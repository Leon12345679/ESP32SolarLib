//
//  SolarDataStore.cpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#include "SolarDataStore.h"

#include "Arduino.h"

#include <Preferences.h>


static const char* prefrenceNamespace = "SolarDataStore";


void SolarDataStore::saveString(String stringToSave, String key)
{
    this->preference.begin(prefrenceNamespace);
    this->preference.putString(key.c_str(), stringToSave.c_str());
    this->preference.end();
}


String SolarDataStore::readSavedString(String key)
{
    String fetchedString = "";
  
    this->preference.begin(prefrenceNamespace);
    fetchedString = this->preference.getString(key.c_str(), ""); // second param is the default value, if fetch failed
    this->preference.end();

    return fetchedString;
}


void SolarDataStore::clearSavedDataForKey(String key)
{
    this->preference.begin(prefrenceNamespace);
    this->preference.remove(key.c_str());
    this->preference.end();
}


void SolarDataStore::clearAllSavedData()
{
    this->preference.begin(prefrenceNamespace);
    this->preference.clear();
    this->preference.end();
}
