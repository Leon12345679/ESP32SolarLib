//
//  SolarSecurity.cpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#include "SolarSecurity.h"

#include "Arduino.h"


bool SolarSecurity::verifyAuthKey(String keyToVerify)
{
    return keyToVerify == SolarSecurity::authKey;
}
