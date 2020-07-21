//
//  ErrorHandlers.h
//  
//
//  Created by Leon Vladimirov on 4/8/20.
//

#ifndef ErrorHandlers_h
#define ErrorHandlers_h

#include "Arduino.h"

#include <ArduinoJson.h>
#include "SolarWebService.h"


void handleSuccess(AsyncWebServerRequest* request);
void handleBadRequest(AsyncWebServerRequest* request);
void handleUnauthorizedRequest(AsyncWebServerRequest* request);
void handlePreconditionFailed(AsyncWebServerRequest* request);


#endif /* ErrorHandlers_h */
