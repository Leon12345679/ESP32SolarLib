//
//  HttpResponseHandler.h
//  
//
//  Created by Leon Vladimirov on 4/8/20.
//

#ifndef HttpResponseHandler_h
#define HttpResponseHandler_h

#include "Arduino.h"

#include <ArduinoJson.h>
#include "SolarWebService.h"


void handleRequest(AsyncWebServerRequest* request, int statusCode);

#endif /* HttpResponseHandler_h */
