//
//  Node.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "Node.h"

namespace GMS
{
    NodeVoid * NodeNull = new NodeVoid () ;
    
    Node::Node ( const NodeType& t )
    : type(t)
    {
        
    }
    
    Node::~Node()
    {
        
    }
    
    NodeType Node::getType() const
    {
        return type ;
    }
    
    NodeVoid::NodeVoid ()
    : GMS::Node(NodeType::Void)
    {
        
    }
    
    Node * NodeVoid::Analyse(GMS::Node *, const GMS::Word &, GMS::WordPeeker &)
    {
        return NodeNull ;
    }
    
    NodeWithName::NodeWithName ( const std::string & n , const NodeType & type )
    : GMS::Node(type) , name(n)
    {
        
    }
    
    const std::string & NodeWithName::getName() const
    {
        return name ;
    }
    
    void NodeWithName::setName(const std::string &n)
    {
        name = n ;
    }
}
