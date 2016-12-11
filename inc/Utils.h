//
//  Utils.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <glob.h>
#include <cassert>

#define GMS_VERSION_MAJOR 1
#define GMS_VERSION_MINOR 0
#define GMS_VERSION_BUILD 1

#define GMS_COMPILER_DEFAULT 0
#define GMS_COMPILER_GCC 1
#define GMS_COMPILER_CLANG 2

namespace GMS
{
    void gmsprint ( const std::vector < std::string > & text ) ;
    std::vector<std::string> ListFilesFromDirectory ( const std::string & directory ) ;
    
    struct Version
    {
        uint8_t Major ;
        uint8_t Minor ;
        uint16_t Build ;
    };
    
    extern Version CurrentVersion ;
    
    std::ostream & operator << ( std::ostream & stream , const Version & version ) ;
}

#endif /* Utils_h */
