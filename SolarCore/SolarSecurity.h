//
//  SolarSecurity.hpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#ifndef SolarSecurity_h
#define SolarSecurity_h

#include "Arduino.h"
#include "mbedtls/md.h"
#include "LibConfig.h"

class SolarSecurity {
private:
    SolarSecurity() {};

    String hash(String stringToHash);
    
public:
    static SolarSecurity& sharedInstance() {
        static SolarSecurity shared;
        return shared;
    }
    
    // Hash of the auth key that is passed from client device
    String authKeyHash;
    
    bool verifyAuthKey(String keyToVerify);
    
};

#endif /* SolarSecurity_h */
