#include "SolarWebService.h"

#include "Arduino.h"

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "SolarDataStore.h"
#include "SolarSecurity.h"
#include "PathHandlers.h"

#include "LibConfig.h"

/*
SOLAR WEB SERVICE IMPLEMENTATION
*/

static const char* authKeyHashVal;

SolarWebService::SolarWebService(const char* authKeyHash)
{
    SolarSecurity::sharedInstance().authKeyHash = authKeyHash;

    server = new AsyncWebServer(80);
    
    // Add path handlers
    server->on("/update", HTTP_GET, &updateFirmware);
    server->on("/reset", HTTP_GET, &resetToFactorySettings);
    
    server->begin();
}


void SolarWebService::startMDNS(const char* domainName, const char* serviceName)
{

    if (!MDNS.begin(domainName)) {

        ESP.restart();
    }

    // Add service to mDNS
    MDNS.addService(serviceName, "tcp", 80);
}


bool SolarWebService::authKeyParamValid(AsyncWebServerRequest* request)
{
    const char* authKeyParamName = "authkey";
    
    if (request->hasParam(authKeyParamName)) {
        
        String authKeyParamVal = request->arg(authKeyParamName);
        
        if (SolarSecurity::sharedInstance().verifyAuthKey(authKeyParamVal.c_str())) {
            return true;
        } else {
            // Wrong auth key
             return false;
        }

    } else {
        // No auth key param
         return false;
    }
}


