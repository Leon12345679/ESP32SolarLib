# ESP32 Solar Lib
A robust lightweight framework for buidling IOT APIs using the ESP32 chip. <br>

# Features 
<ul>
  <li>Auto Connect to WiFi using Smart Config.</li>
  <li>Base API with reset, OTA update functionality and error handlers.</li>
  <li>HTTPS OTA updates.</li>
  <li>API is secured using a client authentication key.</li>
  <li>Extremely fast response times.</li>
  <li>Easily expandable and customizable codebase to fit your needs.</li>
</ul>

# Usage Example
Main .ino file with API configuration
```c++
#include "SolarWebService.h"
#include "WifiConfig.h"

/* Identifiers + Constants /**/

const char* authKey = "17iXyGkWGrnmXRi9JW9ygiCUIkCSiOK0"; // Auth Key to pass from the client device
const char* firmwareVersion = "MyDeviceOS-v-1.0";
const char* modelName = "Solar IOT Device";
const char* mdnsDomainName = "SolarIOTDevice1"; // Domain Name (Your API will be hosted on these domain)
const char* mdnsServiceName = "SolarIOTDevice"; // mDNS Service Type Name

/* SolarWebService Object Pointers /**/

WifiConfig* wifiConfigInstance = nullptr;
SolarWebService* apiInstance = nullptr;

void setup() 
{
  
  wifiConfigInstance = new WifiConfig();
  wifiConfigInstance->connectToWifi();
  apiInstance = new SolarWebService(authKey);

  // Declare a new api "/info" path and implement it in a separate .ino file.
  apiInstance->server->on("/info", HTTP_GET, &getDeviceInfo);
  
  apiInstance->startMDNS(mdnsDomainName, mdnsServiceName);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
```
API Path Implementations .ino file
```c++
void getDeviceInfo(AsyncWebServerRequest* request)
{
    // Use authKeyParamValid to verify the passed Auth Key
    if (SolarWebService::authKeyParamValid(request)) {

         // Create and send the response
         StaticJsonDocument<200> jsonResponse;
         StaticJsonDocument<200> responseData;
         
         responseData["os_version"] = firmwareVersion;
         responseData["uid"] = WiFi.macAddress();
         responseData["model_name"] = modelName;
         responseData["status"] = 200;

         jsonResponse["response"] = responseData;
      
         AsyncResponseStream* response = request->beginResponseStream("application/json");
      
         serializeJson(jsonResponse, *response);
          
         request->send(response);
         
    } else {
        // Invalid auth key
        handleUnauthorizedRequest(request);
    }
}
```

# Dependencies + Installation
1) Make sure these are installed: <br>
<ul>
  <li> <a href="https://github.com/me-no-dev/ESPAsyncWebServer">ESPAsyncWebServer</a> </li>
  <li> <a href="https://github.com/me-no-dev/AsyncTCP">AsyncTCP for ESPAsyncWebServer</a> </li>
  <li> ArduinoJSON - download from the Arduino IDE library manager </li>
</ul> <br>
2) Move the SolarCore folder to your libraries directory - Done!

# Base Paths
Defined in PathHandlers.h and WebService.h <br><br>
<b>/update</b> <br>

Params: <br>
<ul>
  <li><b>authkey:</b> Client Auth Key.</li>
  <li><b>url:</b> New Firmware Binary URL.</li> <br> 
</ul>

Notes: <br> 
The new firmware host's domain must be signed by the set Root CA (DigiCert High Assurance EV Root CA by default). Defined in OTA.h <br>

<b>/reset</b> <br>

Params: <br>
<ul>
  <li><b>authkey:</b> Client Auth Key.</li>
</ul>

# Base Error Handlers
Defined in ErrorHandlers.h <br><br>
<b> 200 </b> ```void handleSuccess(AsyncWebServerRequest* request); ```<br>
<b> 400 </b> ```void handleBadRequest(AsyncWebServerRequest* request); ```<br>
<b> 401 </b> ```void handleUnauthorizedRequest(AsyncWebServerRequest* request); ```<br>
<b> 412 </b> ```void handlePreconditionFailed(AsyncWebServerRequest* request); ```<br>

# Security
<b>Please assess potential threats before using this library.</b> <br>
OTA updates are done over HTTPS. The API is locked by a client auth key. <br> 
Smart Config passes WiFi credentials without encryptiion. <br>
This Library doesn't doesn't support HTTPS out of the box to be lightweight. <br>

# About 
If you have any questions, you can reach me here: Leon.Vladimirov@gmail.com
