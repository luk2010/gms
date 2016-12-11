//
//  Interpreter.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "Interpreter.h"
#include "DllLoader.h"
#include "StdBundle.h"

namespace GMS
{
    Interpreter::Interpreter ( WordPeeker * p )
    : peeker(p)
    {
        Context = new NodeContext ;
        
        StdBundle gmsbundle ;
        gmsbundle.install ( Context ) ;
    }
    
    void Interpreter::interprete ()
    {
        Word next = peeker->next () ;
        
        while ( next.type != 0 )
        {
            Context->Analyse ( Context , next , *peeker ) ;
            next = peeker->next () ;
        }
    }
    
    void Interpreter::loadBundle(const GMS::Bundle &b)
    {
        b.install ( Context ) ;
    }
    
    void Interpreter::loadBundles(const std::string &dir)
    {
        std::vector<std::string> files = ListFilesFromDirectory(dir) ;
        
        for ( auto path : files )
        {
            DllLoader dll ( path ) ;
            if ( dll.load () )
                dll.getBundle() -> install ( Context ) ;
        }
    }
}
