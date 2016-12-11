//
//  NodeProject.cpp
//  GMS
//
//  Created by Jacques Tronconi on 06/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "NodeProject.h"

namespace GMS
{
    NodeProject::NodeProject ( const std::string & name )
    : GMS::NodeObject ( name )
    {
        
        compilerflags = new NodeArray ( "CompilerFlags" ) ;
        
        // Here we have to add some functions.
        
        // Function : SetType %type
        // Sets the type of project you want to do.
        NodeFunction * settype = new NodeFunctionMember ( "SetType" , NodeFunctionType::Normal , 1 ,
            [] ( Node * owner , std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                
                assert( args.size() == 2 && "[Project:SetType] Arguments number given invalid." ) ;
                
                NodeProject * p = reinterpret_cast<NodeProject*>(owner) ;
                if ( !p || p->type != NodeType::Variable || p->vartype != NodeVariableType::Object ) {
                    std::cout << "[Project:SetType] Invalid Function owner." << std::endl;
                    return NodeNull ;
                }
                
                NodeVariableString * type = reinterpret_cast<NodeVariableString*>(args[1]) ;
                if ( !type || type->getType() != NodeType::Variable || type->vartype != NodeVariableType::String ) {
                    std::cout << "[Project:SetType] Invalid string given for type." << std::endl ;
                    return NodeNull ;
                }
                
                p->exectype = type->value ;
                return NodeNull ;
                
        } , this );
        functions["SetType"] = settype ;
        
        NodeFunction * setcompiler = new NodeFunctionMember ( "SetCompiler" , NodeFunctionType::Normal , 1 ,
            [] ( Node * owner , std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                assert( args.size() == 2 && "[Project:SetType] Arguments number given invalid." ) ;
                
                NodeProject * p = reinterpret_cast<NodeProject*>(owner) ;
                if ( !p || p->type != NodeType::Variable || p->vartype != NodeVariableType::Object ) {
                    std::cout << "[Project:SetType] Invalid Function owner." << std::endl;
                    return NodeNull ;
                }
                
                NodeVariableString * type = reinterpret_cast<NodeVariableString*>(args[1]) ;
                if ( !type || type->getType() != NodeType::Variable || type->vartype != NodeVariableType::String ) {
                    std::cout << "[Project:SetType] Invalid string given for type." << std::endl ;
                    return NodeNull ;
                }
                
                p->compiler = type->value ;
                return NodeNull ;
                
        } , this );
        functions["SetCompiler"] = setcompiler ;
        
        
        
    }
}
