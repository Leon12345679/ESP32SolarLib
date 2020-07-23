//
//  HttpResponseHandler.cpp
//  
//
//  Created by Leon Vladimirov on 4/8/20.
//

#include "HttpResponseHandler.h"

#include "Arduino.h"

#include <ArduinoJson.h>
#include "SolarWebService.h"


void handleRequest(AsyncWebServerRequest* request, int statusCode)
{
    StaticJsonDocument<200> jsonResponse;
    StaticJsonDocument<200> responseData;
    
    responseData["status"] = statusCode;
    jsonResponse["response"] = responseData;
    
    AsyncResponseStream* response = request->beginResponseStream("application/json");

    serializeJson(jsonResponse, *response);
    
    request->send(response);
}

