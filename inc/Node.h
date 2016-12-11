//
//  Node.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include "WordPeeker.h"

namespace GMS
{
    enum class NodeType
    {
        None , Void , Function , Variable , Namespace , SubContext , Context
    };
    
    class Node
    {
    public:
        
        Node ( const NodeType & type ) ;
        virtual ~Node () ;
        
        NodeType getType () const ;
        
        virtual Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) = 0 ;
        
        NodeType type ;
    };
    
    class NodeVoid : public Node {
    public:
        
        NodeVoid () ;
        Node * Analyse ( Node * , const Word & , WordPeeker & );
    };
    
    extern NodeVoid * NodeNull ;
    
    class NodeWithName : public Node {
    public:
        
        NodeWithName ( const std::string & name , const NodeType & type ) ;
        
        const std::string & getName () const ;
        void setName ( const std::string & n ) ;
        
    protected:
        
        std::string name ;
    };
}

#endif /* Node_h */
