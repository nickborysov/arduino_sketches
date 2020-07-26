#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "DIR-300NRUB5"
#define STAPSK  "76543210"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);    //Webserver Object

unsigned long updateTime;
bool wasLoaded;

char* accuweatherUpdate = new char[512];
char* openweatherUpdate = new char[512];
const long millisInHour = 60 * 60 * 1000;

String html_1 = R"=====(
<!DOCTYPE html>
<html>
 <head>
 <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
 <meta charset='utf-8'>
 <style>
  body {font-size:140%;}
  #main {display: table; margin: auto;  padding: 0 10px 0 10px; }
  h2 {text-align:center; }
  .button { padding:10px 10px 10px 10px; width:100%;  background-color: #50FF50; font-size: 120%;}
 </style>

 <title>LED Control</title>
</head>
<body>
 <div id='main'>
  <h2>LED Control</h2>
)=====";

void setup() {
  Serial.begin(74880);

  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

    server.on("/", []() {                     //Define the handling function for root path (HTML message)
      printFreeRAM(F("handle root %d"));
      server.send(200, "text/html", html_1);
    });
    server.begin(); //Start the server

  Serial.println("Server listening");
}

void loop() {
  unsigned long currTime = millis();
  if (long(currTime / millisInHour) != long(updateTime / millisInHour) || !wasLoaded) {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Loading weather");

      printFreeRAM(F("start reloadAccuweather %d"));
      reloadAccuweather();
      printFreeRAM(F("enc reloadAccuweather %d"));

      printFreeRAM(F("start reloadOpenweather %d"));
      reloadOpenweather();
      printFreeRAM(F("end reloadOpenweather %d"));
    }
    updateTime = currTime;
    wasLoaded = true;
  }
  
  // handle command from Serial
  if (Serial.available() > 0) {
    printFreeRAM(F("start command %d"));
    String command = Serial.readStringUntil('\n');
    //    char* command = Serial.readline();
    Serial.print("command ");
    Serial.println(command);
    if (command.equals("accuweather")) {
      Serial.println("response");
      Serial.println(accuweatherUpdate);
    }
    if (command.equals("openweather")) {
      Serial.println("response");
      Serial.println(openweatherUpdate);
    }
    printFreeRAM(F("end command %d"));
  }

  // handle http requests
  server.handleClient();  
}

void reloadAccuweather() {
  HTTPClient http; //Object of class HTTPClient
  http.begin("http://dataservice.accuweather.com/forecasts/v1/hourly/12hour/323903?metric=true&apikey=<>");
  int httpCode = http.GET();
  if (httpCode == 0)  {
    Serial.println("error: " + httpCode);
    Serial.println("error: " + http.getString());
    return;
  }
  const size_t CAPACITY = 7640 + 1000;

  // allocate the memory for the document
  DynamicJsonDocument doc(CAPACITY);
  DeserializationError err = deserializeJson(doc, http.getString());
  if (err) {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }
  Serial.print("memoryUsage ");
  Serial.println(doc.memoryUsage());

  delete accuweatherUpdate;
  accuweatherUpdate = new char[512];
  strcat(accuweatherUpdate, "weather#");

  char* tempStr = new char[5];
  char* timeStampString = new char[10];

  // extract the values
  JsonArray respArray = doc.as<JsonArray>();
  for (JsonVariant v : respArray) {
    JsonObject root = v.as<JsonObject>();

    long timeStamp = root["EpochDateTime"];
    float temp = root["Temperature"]["Value"];

    ltoa(timeStamp, timeStampString, 10);
    dtostrf(temp, 1, 2, tempStr);

    strcat(accuweatherUpdate, timeStampString);
    strcat(accuweatherUpdate, ":");
    strcat(accuweatherUpdate, tempStr);
    strcat(accuweatherUpdate, ";");
  }
  Serial.println(accuweatherUpdate);

  delete tempStr;
  delete timeStampString;
}

void reloadOpenweather() {
  HTTPClient http; //Object of class HTTPClient
  http.begin("http://api.openweathermap.org/data/2.5/onecall?lat=49.828480&lon=36.501250&units=metric&exclude=hourly,current,minutely&appid=<>");
  int httpCode = http.GET();
  if (httpCode == 0)  {
    Serial.println("error: " + httpCode);
    Serial.println("error: " + http.getString());
    return;
  }
  const size_t CAPACITY = 5556 + 1000;

  // allocate the memory for the document
  DynamicJsonDocument doc(CAPACITY);
  DeserializationError err = deserializeJson(doc, http.getString());
  if (err) {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }
  Serial.print("memoryUsage ");
  Serial.println(doc.memoryUsage());

  delete openweatherUpdate;
  openweatherUpdate = new char[512];
  strcat(openweatherUpdate, "weather#");

  char* tempStr = new char[5];
  char* timeStampString = new char[10];

  // extract the values
  JsonObject rootObj = doc.as<JsonObject>();
  JsonArray respArray = rootObj["daily"].as<JsonArray>();

  for (JsonVariant v : respArray) {
    JsonObject root = v.as<JsonObject>();
    long timeStamp = root["dt"];
    float temp = root["temp"]["day"];

    ltoa(timeStamp, timeStampString, 10);
    dtostrf(temp, 1, 2, tempStr);

    strcat(openweatherUpdate, timeStampString);
    strcat(openweatherUpdate, ":");
    strcat(openweatherUpdate, tempStr);
    strcat(openweatherUpdate, ";");
  }
  Serial.println(openweatherUpdate);

  delete tempStr;
  delete timeStampString;
}

void printFreeRAM(const __FlashStringHelper *message) {
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)message, system_get_free_heap_size());
  Serial.println(textBuffer);
  delete textBuffer;
}

// response example
/*
  ....
  Connected to DIR-300NRUB5
  IP address: 192.168.31.82
  Server listening
  Loading weather
  start reloadAccuweather 50584
  memoryUsage 7640
  weather#1595541600:14.30;1595545200:13.50;1595548800:13.90;1595552400:12.10;1595556000:13.00;1595559600:13.70;1595563200:15.80;1595566800:18.00;1595570400:20.00;1595574000:21.10;1595577600:21.80;1595581200:22.40;
  enc reloadAccuweather 50120
  start reloadOpenweather 50120
  memoryUsage 5556
  weather#1595581200:21.83;1595667600:24.11;1595754000:27.39;1595840400:28.03;1595926800:29.20;1596013200:26.86;1596099600:27.47;1596186000:29.83;
  end reloadOpenweather 50040
*/
