//
//  SolarSecurity.hpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#ifndef SolarSecurity_h
#define SolarSecurity_h

#include "Arduino.h"

class SolarSecurity {
private:
    SolarSecurity() {};
    
public:
    static SolarSecurity& sharedInstance() {
        static SolarSecurity shared;
        return shared;
    }
    
    // auth key passed from client device
    String authKey;
    
    bool verifyAuthKey(String keyToVerify);
    
};

#endif /* SolarSecurity_h */
