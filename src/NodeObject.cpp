//
//  NodeObject.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "NodeObject.h"

namespace GMS
{
    NodeObject::NodeObject ( const std::string & name )
    : GMS::NodeVariable(name, NodeVariableType::Object)
    {
        
    }
    
    Node* NodeObject::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        // Check if it's a function.
        
        {
            auto it = functions.find ( word.content ) ;
            if ( it != functions.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        // Let NodeVariable checks for us.
        
        return NodeVariable::Analyse(Context, word, peeker) ;
    }
    
    NodeArray::NodeArray ( const std::string & name )
    : GMS::NodeObject( name )
    {
        construct() ;
    }
    
    NodeArray::NodeArray ( const std::string & name , const std::vector<NodeVariable*> data )
    : GMS::NodeObject( name ) , arr( data )
    {
        construct() ;
    }
    
    void NodeArray::construct()
    {
        // An Array have the following functions : add ( variable ) , remove ( name ) , clear , count , size , Get .
        
        NodeFunction * add = new NodeFunctionMember ( "Add" , NodeFunctionType::Normal , 1 ,
            [] ( Node * owner , std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                
                assert( args.size() == 2 && "[Project:SetType] Arguments number given invalid." ) ;
                
                NodeArray * p = reinterpret_cast<NodeArray*>(owner) ;
                if ( !p || p->type != NodeType::Variable || p->vartype != NodeVariableType::Object ) {
                    std::cout << "[Array:Add] Invalid Function owner." << std::endl;
                    return NodeNull ;
                }
                
                NodeVariable * obj = reinterpret_cast<NodeVariable*>(args[1]) ;
                if ( !obj || p->type != NodeType::Variable ) {
                    std::cout << "[Array:Add] Invalid Node given." << std::endl;
                    return NodeNull ;
                }
                
                p->arr.push_back(obj);
                return NodeNull ;
                
        } , this ) ;
        functions["Add"] = add ;
        
        
    }
}
