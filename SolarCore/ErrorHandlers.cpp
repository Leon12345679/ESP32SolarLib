//
//  ErrorHandlers.cpp
//  
//
//  Created by Leon Vladimirov on 4/8/20.
//

#include "ErrorHandlers.h"

#include "Arduino.h"

#include <ArduinoJson.h>
#include "SolarWebService.h"


void handleSuccess(AsyncWebServerRequest* request)
{
    StaticJsonDocument<200> jsonResponse;
    StaticJsonDocument<200> responseData;
    
    responseData["status"] = 200;
    jsonResponse["response"] = responseData;
    
    AsyncResponseStream* response = request->beginResponseStream("application/json");

    serializeJson(jsonResponse, *response);
    
    request->send(response);
}


void handleBadRequest(AsyncWebServerRequest* request)
{
    StaticJsonDocument<200> jsonResponse;
    StaticJsonDocument<200> responseData;
    
    responseData["status"] = 400;
    
    jsonResponse["response"] = responseData;
    
    AsyncResponseStream* response = request->beginResponseStream("application/json");

    serializeJson(jsonResponse, *response);
    
    request->send(response);
}


void handleUnauthorizedRequest(AsyncWebServerRequest* request)
{
    StaticJsonDocument<200> jsonResponse;
    StaticJsonDocument<200> responseData;
    
    responseData["status"] = 401;
    jsonResponse["response"] = responseData;
    
    AsyncResponseStream* response = request->beginResponseStream("application/json");

    serializeJson(jsonResponse, *response);
    
    request->send(response);
}


void handlePreconditionFailed(AsyncWebServerRequest* request)
{
    StaticJsonDocument<200> jsonResponse;
    StaticJsonDocument<200> responseData;
    
    responseData["status"] = 412;
    jsonResponse["response"] = responseData;
    
    AsyncResponseStream* response = request->beginResponseStream("application/json");

    serializeJson(jsonResponse, *response);
    
    request->send(response);
}
