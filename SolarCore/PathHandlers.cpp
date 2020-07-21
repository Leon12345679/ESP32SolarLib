//
//  PathHandlers.cpp
//  
//
//  Created by Leon Vladimirov on 4/5/20.
//

#include "PathHandlers.h"

#include "Arduino.h"

#include <ArduinoJson.h>

#include "SolarDataStore.h"
#include "SolarSecurity.h"
#include "SolarWebService.h"
#include "SolarOTA.h"
#include "ErrorHandlers.h"


/*
PATH HANDLERS
 
Must be non member functions
*/


void updateFirmware(AsyncWebServerRequest* request)
{
    if (SolarWebService::authKeyParamValid(request)) {
        
        const char* firmwareURLParamName = "url";
        
        if (request->hasParam(firmwareURLParamName)) {
            // Can OTA update
            // Respond with 200 and attempt
            handleSuccess(request);
            
            String firmwareURLParamaVal = request->arg(firmwareURLParamName);
            
            SolarOTA updater = SolarOTA();
            
            updater.updateFirmwareFrom(firmwareURLParamaVal.c_str());

        } else {
            // URL param not set
            handleBadRequest(request);
        }
        
    } else {
        handleUnauthorizedRequest(request);
    }
}


// Fully erases the device, WiFi config included
void resetToFactorySettings(AsyncWebServerRequest* request)
{
    if (SolarWebService::authKeyParamValid(request)) {
        
        // Erase config and restart
        
        SolarDataStore::sharedInstance().clearAllSavedData();
        
        WiFi.disconnect();
        
        ESP.restart();
        
    }  else {
        // Wrong or no Auth Key
        handleUnauthorizedRequest(request);
    }
  
}

