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
String html_index;

unsigned long updateTime;
bool wasLoaded;

//DynamicJsonDocument accuweatherDoc(8640);
//DynamicJsonDocument openweatherDoc(6556);
char* accuweatherUpdate = new char[512];
char* openweatherUpdate = new char[512];
const long millisInHour = 60 * 60 * 1000;


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

  setupHtml();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleGetData);
  server.begin(); //Start the server

  Serial.println("Server listening");
}

void handleRoot() {
  printFreeRAM(F("handle root %d"));
  server.send(200, "text/html", html_index);
}

void handleGetData() {
  printFreeRAM(F("handle data %d"));

  StaticJsonDocument<1024> doc;
  doc["Accuweather_forecast"] = accuweatherUpdate;
  doc["Openweather_forecast"] = openweatherUpdate;

  String json;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
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
      Serial.print("weather#");
      Serial.println(accuweatherUpdate);
    }
    if (command.equals("openweather")) {
      Serial.print("weather#");
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

  DynamicJsonDocument accuweatherDoc(8640);
  DeserializationError err = deserializeJson(accuweatherDoc, http.getString());
  if (err) {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }

  delete accuweatherUpdate;
  accuweatherUpdate = new char[512];

  char* tempStr = new char[5];
  char* timeStampString = new char[10];

  // extract the values
  JsonArray respArray = accuweatherDoc.as<JsonArray>();
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

  DynamicJsonDocument openweatherDoc(6556);
  DeserializationError err = deserializeJson(openweatherDoc, http.getString());
  if (err) {
    Serial.println(err.c_str());
    Serial.println("error: " + http.getString());
    return;
  }

  delete openweatherUpdate;
  openweatherUpdate = new char[512];

  char* tempStr = new char[5];
  char* timeStampString = new char[10];

  // extract the values
  JsonObject rootObj = openweatherDoc.as<JsonObject>();
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


// setupHtml set html files. Create fucntioon to put it in the end of file
void setupHtml() {
  html_index = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <meta charset="utf-8" />

    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js"></script>

    <style>
        body {
            font-size: 140%;
            background-color: white;
            background: white;
        }

        #main {
            display: table;
            margin: auto;
            padding: 0 10px 0 10px;
        }

        .header-h1 {
            position: relative;
            margin-bottom: .5rem;
            text-align: center;
        }

        .header-h1 h1 {
            display: inline-block;
            background: #fff;
            margin-bottom: 0;
            font-size: 1.5rem;
            text-transform: uppercase;
            padding: .5rem 1.5rem;
            border: .125rem solid #6a1b9a;
            color: #6a1b9a;
        }

        .header-h1 h1::after {
            content: "";
            position: absolute;
            background: #6a1b9a;
            height: .125rem;
            left: 0;
            top: 50%;
            width: 100%;
            transform: translateY(-50%);
            z-index: -999;
        }

        .header-h1-dark h1 {
            background: #6a1b9a;
            color: #fff;
        }

        table.purple-table {
            border: 1px solid #6a1b9a;
        }

        .table td {
            border-top: 0px;
            border-bottom: 1px solid #6a1b9a;
        }
    </style>

    <script>

        const testResp = {
            "OpenWeather forecast": "1595541600:14.30;1595545200:13.50;1595548800:13.90;1595552400:12.10;1595556000:13.00;1595559600:13.70;1595563200:15.80;1595566800:18.00;1595570400:20.00;1595574000:21.10;1595577600:21.80;1595581200:22.40;",
            "AccuWeather forecast": "1595581200:21.83;1595667600:24.11;1595754000:27.39;1595840400:28.03;1595926800:29.20;1596013200:26.86;1596099600:27.47;1596186000:29.83",
            "OneWire sensor": "1595581200:21.83;"
        }

        function loadPage() {
            loadWeatherData();
            // showWeatherData(testResp);
        }
        function loadWeatherData() {
            const Http = new XMLHttpRequest();
            const url = '/data';
            Http.open("GET", url);
            Http.send();

            Http.onreadystatechange = (e) => {
                let resp = JSON.parse(Http.responseText);
                showWeatherData(resp);
            }
        }
        function showWeatherData(data) {
            // parse data
            var resp = [];
            for (const key in data) {
                const element = data[key];

                var espResp = parseESPForecast(key, element);
                resp = resp.concat(espResp);
            }
            resp.sort((item1, item2) => {
                if (item1.date > item2.date) return 1;
                if (item1.date < item2.date) return -1;
                return 0;
            })

            // show weather
            let weatherTable = document.getElementById("weather");
            weatherTable.innerHTML = '';

            var titleView = document.createElement("tr");
            titleView.innerHTML = `
            <tr>
                <td>Provider</td>
                <td>Date</td>
                <td>Value</td>
            </tr>
            `;

            weatherTable.appendChild(titleView);

            resp.forEach(item => {
                var typeView = document.createElement("td");
                typeView.innerText = item.type;

                var dateView = document.createElement("td");
                dateView.innerText = item.date.toLocaleString();

                var tempView = document.createElement("td");
                tempView.innerText = item.temp;

                var row = document.createElement("tr");
                row.appendChild(typeView);
                row.appendChild(dateView);
                row.appendChild(tempView);

                weatherTable.appendChild(row);
            });
        }


        function parseESPForecast(type, data) {
            var resp = [];
            var weatherItems = data.split(";");
            weatherItems.forEach(item => {
                if (item === '') {
                    return;
                }
                weatherData = item.split(":");
                resp = resp.concat({
                    type: type,
                    date: new Date(weatherData[0] * 1000),
                    temp: weatherData[1]
                });
            });
            return resp;
        }


    </script>

    <title>Home weather</title>
</head>

<body onload="loadPage()" class="bg-dark">
    <div class="container text-white main">
        <div class="header-h1 header-h1-dark">
            <h1>Home weather</h1>
        </div>
        <table id="weather" class="table table-dark table-hover purple-table"></table>
    </div>
</body>

</html>
)=====";
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
