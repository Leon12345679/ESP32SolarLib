//
//  WifiConfig.cpp
//  
//
//  Created by Leon Vladimirov on 4/4/20.
//

#include "WifiConfig.h"

#include "Arduino.h"


#include <WiFi.h>
#include "SolarDataStore.h"

#include "LibConfig.h"


static String wifiSSIDKey = "wifiSSID";
static String wifiPasswordKey = "wifiPassword";

void WifiConfig::connectToWifi()
{
    
    this->wifiSSID = SolarDataStore::sharedInstance().readSavedString(wifiSSIDKey);
    this->wifiPassword = SolarDataStore::sharedInstance().readSavedString(wifiPasswordKey);

    this->attemptConnection();
    
}

void WifiConfig::smartConfig()
{
    
    WiFi.mode(WIFI_STA);

    WiFi.beginSmartConfig();

     // put your setup code here, to run once:
    while (!WiFi.smartConfigDone()) {
        
        delay(1000);

    }

     // Save WiFi credentials to EEPROM
    wifiSSID = WiFi.SSID();
    wifiPassword = WiFi.psk();
    
    SolarDataStore::sharedInstance().saveString(wifiSSID, wifiSSIDKey);
    SolarDataStore::sharedInstance().saveString(wifiPassword, wifiPasswordKey);
    
    WiFi.stopSmartConfig();
}


void WifiConfig::attemptConnection()
{
    
    WiFi.mode(WIFI_STA);
     
    if (wifiSSID.c_str() && !wifiSSID.c_str()[0]) {
        
        this->smartConfig();
        
    }
    
    WiFi.begin(wifiSSID.c_str(), wifiPassword.c_str());
    
    // Try to connect to WiFi if max retries exceeded - erase current SSID and Password and restart
    // Needed if the user changes their password
    uint connectionRetries = 0;
    
    while (WiFi.status() != WL_CONNECTED) {
        if (connectionRetries > 100) {
                        
            SolarDataStore::sharedInstance().clearSavedDataForKey(wifiSSIDKey);
            SolarDataStore::sharedInstance().clearSavedDataForKey(wifiPasswordKey);
            
            ESP.restart();
        }
        
        delay(500);
        connectionRetries++;
        
      }
}
