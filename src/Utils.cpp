//
//  Utils.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "Utils.h"

namespace GMS
{
    void gmsprint ( const std::vector<std::string> & text )
    {
        if ( text.size() >= 1 )
        {
            std::string rtext = text.at(0);
            size_t curi = 1 ;
            
            for ( auto it = rtext.begin() ; it != rtext.end() ; it ++ )
            {
                if ( *it != '%' ) {
                    std::cout << *it ;
                    continue ;
                }
                
                if ( *it == '%' && *(it+1) == 's' ) {
                    if ( text.size() > curi )
                    {
                        std::cout << text.at(curi) ;
                        curi ++ ; it ++ ;
                        continue ;
                    }
                    else
                    {
                        std::cout << "%s" ;
                        it ++ ; continue ;
                    }
                }
            }
            
            std::cout << std::endl;
        }
    }
    
    std::vector<std::string> ListFilesFromDirectory ( const std::string & directory )
    {
        glob_t globresult ;
        std::string path = directory + "*" ;
        std::vector < std::string > result ;
        
        if ( glob(path.c_str(), GLOB_TILDE, NULL, &globresult) == 0 )
        {
            for ( unsigned int i = 0 ; i < globresult.gl_pathc ; ++i )
            {
                result.push_back(std::string(globresult.gl_pathv[i])) ;
                std::cout << "Found path '" << globresult.gl_pathv[i] << "'." << std::endl;
            }
            
            globfree(&globresult) ;
        }
        
        return result ;
    }
    
    Version CurrentVersion = {
        GMS_VERSION_MAJOR ,
        GMS_VERSION_MINOR ,
        GMS_VERSION_BUILD
    } ;
    
    std::ostream & operator << ( std::ostream & stream , const Version & version )
    {
        stream
        << (unsigned int) version.Major << "."
        << (unsigned int) version.Minor << "."
        << (unsigned int) version.Build ;
        
        return stream ;
    }
}
