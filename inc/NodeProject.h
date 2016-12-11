//
//  NodeProject.h
//  GMS
//
//  Created by Jacques Tronconi on 06/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef NodeProject_h
#define NodeProject_h

#include "NodeObject.h"

namespace GMS
{
    /// @brief Defines a GMS Project .
    class NodeProject : public NodeObject
    {
    public:
        
        NodeProject ( const std::string & name ) ;
        
        std::string exectype ;
        std::string compiler ;
        NodeArray * compilerflags ;
    };
}

#endif /* NodeProject_h */
