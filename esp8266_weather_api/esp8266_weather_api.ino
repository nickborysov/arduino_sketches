#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "secrets.h"
// run "make prebuild" to generate header with resources
#include "build/index.h"

#ifndef STASSID
#define STASSID "DIR-300NRUB5"
#define STAPSK "76543210"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80); //Webserver Object

const char *accuWeatherUrl = strcat("http://dataservice.accuweather.com/forecasts/v1/hourly/12hour/323903?metric=true&apikey=", accuWeatherKey);
const char *opneWeatherUrl = strcat("http://api.openweathermap.org/data/2.5/onecall?lat=49.828480&lon=36.501250&units=metric&exclude=hourly,current,minutely&appid=", openWeatherKey);

unsigned long updateTime;
bool wasLoaded;

DynamicJsonDocument weatherJSON(5000);
const long millisInHour = 60 * 60 * 1000;

void setup()
{
  Serial.begin(74880);

  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleGetData);
  server.begin(); //Start the server

  Serial.println("Server listening");
}

void handleRoot()
{
  printFreeRAM(F("handle root %d"));
  server.send(200, "text/html", html_index);
}

void handleGetData()
{
  printFreeRAM(F("handle data %d"));
  String json;
  serializeJson(weatherJSON, json);
  server.send(200, "application/json", json);
}

void loop()
{
  unsigned long currTime = millis();
  if (long(currTime / millisInHour) != long(updateTime / millisInHour) || !wasLoaded)
  {
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
  if (Serial.available() > 0)
  {
    printFreeRAM(F("start command %d"));
    String command = Serial.readStringUntil('\n');
    Serial.print("command ");
    Serial.println(command);
    if (command.equals("accuweather"))
    {
      Serial.println("weather#");
      String json;
      serializeJson(weatherJSON["accuweather"], json);
      Serial.println(json);
    }
    if (command.equals("openweather"))
    {
      Serial.print("weather#");
      String json;
      serializeJson(weatherJSON["openweather"], json);
      Serial.println(json);
    }
    if (command.startsWith("sensor"))
    {
      //      format of command sensor should be 'sensorXXX:timestamp:value'
      String sensorId = command.substring(0, 9);
      String timeStamp = command.substring(10, 20);
      String value = command.substring(21, 26);
      JsonArray weatherRepsArray;
      if (weatherJSON.containsKey(sensorId))
      {
        weatherRepsArray = weatherJSON[sensorId].as<JsonArray>();
      }
      else
      {
        weatherRepsArray = weatherJSON.createNestedArray(sensorId);
      }
      JsonObject obj = weatherRepsArray.createNestedObject();
      obj["timestamp"] = timeStamp;
      obj["temperature"] = value;
      Serial.println(timeStamp);
      Serial.println(value);
    }
    printFreeRAM(F("end command %d"));
  }

  // handle http requests
  server.handleClient();
}

void reloadAccuweather()
{
  HTTPClient http; //Object of class HTTPClient
  http.begin(accuWeatherUrl);
  int httpCode = http.GET();
  if (httpCode == 0)
  {
    Serial.println("error: " + httpCode);
    Serial.println("error: " + http.getString());
    return;
  }

  DynamicJsonDocument accuweather(8640);

  DeserializationError err = deserializeJson(accuweather, http.getString());
  if (err)
  {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }

  weatherJSON.remove("accuweather");
  JsonArray weatherRepsArray = weatherJSON.createNestedArray("accuweather");
  // extract the values
  JsonArray respArray = accuweather.as<JsonArray>();
  for (JsonVariant v : respArray)
  {
    JsonObject root = v.as<JsonObject>();

    long timeStamp = root["EpochDateTime"];
    float temp = root["Temperature"]["Value"];

    JsonObject obj = weatherRepsArray.createNestedObject();
    obj["timestamp"] = timeStamp;
    obj["temperature"] = temp;
  }
}

void reloadOpenweather()
{
  HTTPClient http; //Object of class HTTPClient
  http.begin(opneWeatherUrl);
  int httpCode = http.GET();
  if (httpCode == 0)
  {
    Serial.println("error: " + httpCode);
    Serial.println("error: " + http.getString());
    return;
  }

  DynamicJsonDocument openweatherDoc(6556);
  DeserializationError err = deserializeJson(openweatherDoc, http.getString());
  if (err)
  {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }

  weatherJSON.remove("openweather");
  JsonArray weatherRepsArray = weatherJSON.createNestedArray("openweather");
  // extract the values
  JsonObject rootObj = openweatherDoc.as<JsonObject>();
  JsonArray respArray = rootObj["daily"].as<JsonArray>();

  for (JsonVariant v : respArray)
  {
    JsonObject root = v.as<JsonObject>();
    long timeStamp = root["dt"];
    float temp = root["temp"]["day"];
    uint16_t humidity = root["humidity"];

    JsonObject obj = weatherRepsArray.createNestedObject();
    obj["timestamp"] = timeStamp;
    obj["temperature"] = temp;
    obj["humidity"] = humidity;
  }
}

void printFreeRAM(const __FlashStringHelper *message)
{
  char *textBuffer = new char[30];
  sprintf_P(textBuffer, (PGM_P)message, system_get_free_heap_size());
  Serial.println(textBuffer);
  delete textBuffer;
}
