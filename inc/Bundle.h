//
//  Bundle.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef Bundle_h
#define Bundle_h

#include "NodeContext.h"

namespace GMS
{
    class Bundle
    {
    public:
        
        Bundle ( ) ;
        virtual ~Bundle ( ) ;
        
        virtual void install ( NodeContext * ctxt ) const = 0 ;
    };
}

#endif /* Bundle_h */
