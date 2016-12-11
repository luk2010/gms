//
//  StdBundle.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef StdBundle_h
#define StdBundle_h

#include "Bundle.h"

namespace GMS
{
    class StdBundle : public Bundle
    {
    public:
        
        StdBundle ( ) ;
        
        void install ( NodeContext * Context ) const ;
    };
}

#endif /* StdBundle_h */
