//
//  PathHandlers.hpp
//  
//
//  Created by Leon Vladimirov on 4/5/20.
//

#ifndef PathHandlers_h
#define PathHandlers_h

#include "Arduino.h"

#include <ArduinoJson.h>

#include "SolarDataStore.h"
#include "SolarSecurity.h"
#include "SolarWebService.h"
#include "SolarOTA.h"
#include "ErrorHandlers.h"


// Base API Path Handlers
void updateFirmware(AsyncWebServerRequest* request);
void resetToFactorySettings(AsyncWebServerRequest* request);


#endif /* PathHandlers_h */
