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


void handleRequest(AsyncWebServerRequest* request, int statusCode);

#endif /* ErrorHandlers_h */
