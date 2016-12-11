//
//  Interpreter.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include "NodeContext.h"
#include "Bundle.h"

namespace GMS
{
    class Interpreter
    {
    public:
        
        Interpreter ( WordPeeker * p ) ;
        
        void interprete () ;
        
        void loadBundle ( const Bundle & b ) ;
        void loadBundles ( const std::string & dir ) ;
        
    protected:
        
        WordPeeker * peeker ;
        NodeContext * Context ;
    };
}

#endif /* Interpreter_h */
