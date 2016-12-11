//
//  DllLoader.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "DllLoader.h"

namespace GMS
{
    DllLoader::DllLoader ( const std::string & p )
    : path ( p ) , handle( nullptr )
    {
        
    }
    
    DllLoader::~DllLoader()
    {
        
    }
    
    bool DllLoader::load()
    {
        DYNLIB_HANDLE dhdl = DYNLIB_LOAD(path.c_str()) ;
        if ( !dhdl )
            return false ;
        
        typedef Bundle * (*plugcreatebundle_t) ( void ) ;
        plugcreatebundle_t plugCreateBundle = (plugcreatebundle_t) DYNLIB_GETSYM(dhdl, "CreateBundle") ;
        
        if ( !plugCreateBundle )
        {
            DYNLIB_UNLOAD(dhdl) ;
            return false ;
        }
        
        bundle = plugCreateBundle ( ) ;
        
        if ( !bundle )
        {
            DYNLIB_UNLOAD(dhdl);
            return false ;
        }
        
        handle = dhdl ;
        return true ;
    }
    
    Bundle * DllLoader::getBundle()
    {
        return bundle ;
    }
}
