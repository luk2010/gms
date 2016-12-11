//
//  NodeVariable.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef NodeVariable_h
#define NodeVariable_h

#include "Node.h"

namespace GMS
{
    enum class NodeVariableType
    {
        String , Object 
    };
    
    // A Variable is a node that can contain a specific value .
    class NodeVariable : public NodeWithName {
    public:
        
        NodeVariableType vartype ;
        
    public:
        
        NodeVariable ( const std::string & name , const NodeVariableType & t ) ;
        NodeVariable ( const std::string & name , const NodeType & nt , const NodeVariableType & vt ) ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker );
    };
    
    class NodeVariableString : public NodeVariable {
    public:
        
        std::string value ;
        
    public:
        
        NodeVariableString ( const std::string & name , const std::string & value ) ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
    };
}

#endif /* NodeVariable_h */
