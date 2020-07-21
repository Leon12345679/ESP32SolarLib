//
//  WifiConfig.hp
//  
//
//  Created by Leon Vladimirov on 4/4/20.
//

#ifndef WifiConfig_h
#define WifiConfig_h

#include "Arduino.h"


#include <WiFi.h>
#include "SolarDataStore.h"

#include "LibConfig.h"


class WifiConfig {
    
private:
    String wifiSSID;
    String wifiPassword;
    
protected:
    void attemptConnection();
    void smartConfig();
    
public:
    void connectToWifi();
    
};

#endif /* WifiConfig_h */
