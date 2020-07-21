//
//  SolarSecurity.cpp
//  
//
//  Created by Leon Vladimirov on 3/26/20.
//

#include "SolarSecurity.h"

#include "Arduino.h"
#include "mbedtls/md.h"
#include "LibConfig.h"

String SolarSecurity::hash(String stringToHash)
{
    // Input String -> SHA256 Byte Array
    byte shaResult[32];
     
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
     
    const size_t stringToHashLength = stringToHash.length();
     
    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char*) stringToHash.c_str(), stringToHashLength);
    mbedtls_md_finish(&ctx, shaResult);
    mbedtls_md_free(&ctx);
    
    // Convert SHA256 Byte array into Char array
    
    String hashStr = "";
    
    for(int i= 0; i< sizeof(shaResult); i++) {
        char hashCharArray[3];

        sprintf(hashCharArray, "%02x", (int)shaResult[i]);
        
        hashStr += hashCharArray;
    }
    
    return hashStr;  // Return hashed input String
    
}


bool SolarSecurity::verifyAuthKey(String keyToVerify)
{
    return this->hash(keyToVerify) == SolarSecurity::authKeyHash;
}
