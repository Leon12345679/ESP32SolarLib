#ifndef SolarWebService_h
#define SolarWebService_h

#include "Arduino.h"

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

#include "SolarDataStore.h"
#include "SolarSecurity.h"
#include "PathHandlers.h"

#include "LibConfig.h"


class SolarWebService {
 
public:
    SolarWebService(const char*  authKeyHash); // init
        
    AsyncWebServer* server; // server ptr for adding new paths
    
    static bool authKeyParamValid(AsyncWebServerRequest* request);

    void startMDNS(const char*  domainName, const char*  serviceName);    
    
}; // SolarWebService end

#endif
