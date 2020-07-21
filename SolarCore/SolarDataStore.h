//
//  SolarDataStore.hpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#ifndef SolarDataStore_h
#define SolarDataStore_h

#include "Arduino.h"

#include <Preferences.h>


class SolarDataStore {
private:
    SolarDataStore() {};
    Preferences preference;
    
public:
    static SolarDataStore& sharedInstance() {
        static SolarDataStore shared;
        return shared;
    }
    
    void saveString(String stringToSave, String key);
    
    String readSavedString(String key);

    void clearSavedDataForKey(String key);
    
    void clearAllSavedData();
    
}; // SolarDataStore end


#endif /* SolarDataStore_h */
