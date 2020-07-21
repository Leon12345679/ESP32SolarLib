//
//  SolarOTA.h
//  
//
//  Created by Leon Vladimirov on 3/27/20.
//

#ifndef SolarOTA_h
#define SolarOTA_h

#include "Arduino.h"

#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <time.h>


class SolarOTA {
private:
    void setTime();
    
public:
    bool updateFirmwareFrom(String url);
};

#endif /* SolarOTA.h */
