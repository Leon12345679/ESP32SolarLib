# ESP32 Solar Lib
A robust and lightweight framework for buidling IoT APIs using the ESP32 chip. <br>

# Features 
<ul>
  <li>Auto Connect to WiFi using Smart Config.</li>
  <li>Base API with reset, OTA update functionality.</li>
  <li>HTTPS OTA updates.</li>
  <li>API is secured using a client authentication key.</li>
  <li>Extremely fast response times.</li>
  <li>Easily expandable and customizable codebase to fit your needs.</li>
</ul>

# Usage Example
Let's build a simple API that allows us to access info about the device. <br>
Here is the Main .ino file with API configuration
```c++
#include "SolarWebService.h"
#include "WifiConfig.h"

/* Device Identifiers /**/

const char* authKey = "17iXyGkWGrnmXRi9JW9ygiCUIkCSiOK0"; // Auth Key to pass from the client device
const char* firmwareVersion = "MyDeviceOS-v-1.0";
const char* modelName = "Solar IOT Device";
const char* mdnsDomainName = "SolarIOTDevice1"; // Domain Name (Your API will be hosted on this domain)
const char* mdnsServiceName = "SolarIOTDevice"; // mDNS Service Type Name

/* Solar Library Object Pointers /**/

WifiConfig* wifiConfigInstance = nullptr;
SolarWebService* apiInstance = nullptr;

void setup() 
{
  
  wifiConfigInstance = new WifiConfig();
  wifiConfigInstance->connectToWifi();
  apiInstance = new SolarWebService(authKey);

  // Declare a new api "/info" path and implement it in a separate .ino file.
  // This will be our device info endpoint.
  apiInstance->server->on("/info", HTTP_GET, &getDeviceInfo);
  
  apiInstance->startMDNS(mdnsDomainName, mdnsServiceName);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
```
Let us now implement the endpoint. <br>
Here is the API Path Implementations .ino file
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
        // Invalid or no Auth Key -> Unauthorized request
        // handleRequest is defined in HttpResponseHandler.h
        handleRequest(request, 401);
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
Firmware host must be signed by set Root CA (DigiCert High Assurance EV Root CA by default). Defined in OTA.h <br><br>

<b>/reset</b> <br>

Params: <br>
<ul>
  <li><b>authkey:</b> Client Auth Key.</li>
</ul>


# Security
<b>Please assess potential threats before using this library.</b> <br>
OTA updates are done over HTTPS. The API is locked by a client auth key. <br> 
Smart Config passes WiFi credentials without encryption. <br>
This Library doesn't doesn't support HTTPS out of the box to be lightweight. <br>

# About 
If you have any questions, you can reach me here: Leon.Vladimirov@gmail.com
