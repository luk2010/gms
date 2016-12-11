//
//  NodeObject.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef NodeObject_h
#define NodeObject_h

#include "Node.h"

#include "NodeFunction.h"
#include "NodeVariable.h"

namespace GMS
{
    /// @brief Defines a basic Object in GMS's language.
    /// An Object derives also from NodeVariable , as it can be stored in another object, can have
    /// function, and can be stored in a structure variable.
    class NodeObject : public NodeVariable {
    public:
        
        std::map<std::string , NodeFunction * > functions ;
        
        NodeObject ( const std::string & name ) ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
    };
    
    // Defines a standard Array of Variables.
    class NodeArray : public NodeObject
    {
    public:
        
        std::vector < NodeVariable * > arr ;
        
    public:
        
        NodeArray ( const std::string & name ) ;
        NodeArray ( const std::string & name , const std::vector < NodeVariable* > data ) ;
        
    protected:
        
        void construct () ;
    };
}

#endif /* NodeObject_h */
