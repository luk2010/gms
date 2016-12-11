//
//  StdBundle.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "StdBundle.h"

#include "NodeProject.h"

namespace GMS
{
    StdBundle::StdBundle ()
    : GMS::Bundle()
    {
        
    }
    
    void StdBundle::install(GMS::NodeContext *Context) const
    {
        if ( !Context )
            return ;
        
        // Create the "GMS" namespace .
        NodeNamespace* ngms = new NodeNamespace ( "GMS" ) ;
        Context -> namespaces["GMS"] = ngms ;
        
        {
            // Function : VersionCheck %version -> NodeNull
            // Check if the given required version is at least less than running version.
            NodeFunction* fversioncheck = new NodeFunction ( "VersionCheck" , NodeFunctionType::Normal , 1 ,
                [] ( std::vector<Node*>& args , WordPeeker & ) -> Node* {
                    
                    if ( args[1] ->getType() == NodeType::Variable )
                    {
                        NodeVariable * var = reinterpret_cast<NodeVariable*>(args[1]) ;
                        if ( var->vartype == NodeVariableType::String )
                        {
                            NodeVariableString * str = reinterpret_cast<NodeVariableString*>(args[1]) ;
                            
                            uint8_t maj = str->value[0] ;
                            uint8_t min = str->value[2] ;
                            
                            if ( maj > GMS_VERSION_MAJOR || ( maj == GMS_VERSION_MAJOR && min > GMS_VERSION_MINOR &&
                                                             (min != 0 && GMS_VERSION_MINOR != 0) ) )
                            {
                                std::cout << "Invalid Version for given script." << std::endl;
                                return NodeNull ;
                            }
                        }
                    }
                    
                    return NodeNull ;
            }) ;
            ngms -> functions["VersionCheck"] = fversioncheck ;
            
            // Function : Print %sentence %args... -> Null
            // Print a given sentence to the command prompt.
            NodeFunction * fprint = new NodeFunction ( "Print" , NodeFunctionType::Variadic , 0 ,
                [] ( std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                    
                    Node* str = args[0] -> Analyse( args[0] , peeker.next() , peeker ) ;
                    
                    if ( str ->getType() == NodeType::Variable )
                    {
                        NodeVariable * var = reinterpret_cast<NodeVariable*>(str) ;
                        if ( var->vartype == NodeVariableType::String )
                        {
                            NodeVariableString * nstr = reinterpret_cast<NodeVariableString*>(str) ;
                            
                            for ( char * c = & nstr->value[0] ; *c != '\0' ; c++ )
                            {
                                if ( *c == '%' && *(c+1) != '%' ) {
                                    c++ ;
                                    
                                    Node * result = args[0] -> Analyse( args[0] , peeker.next() , peeker ) ;
                                    
                                    if ( result -> getType() == NodeType::Variable &&
                                        reinterpret_cast<NodeVariable*>(result)->vartype == NodeVariableType::String )
                                    {
                                        NodeVariableString * s = reinterpret_cast<NodeVariableString*>(result) ;
                                        std::cout << s ;
                                    }
                                    else
                                    {
                                        std::cout << "%?" ;
                                    }
                                }
                                
                                else
                                    std::cout.put(*c) ;
                            }
                            
                            std::cout << std::endl ;
                        }
                    }
                    
                    return NodeNull ;
                    
            }) ;
            ngms -> functions["Print"] = fprint ;
            
            // Function : Var %name %expression -> Null
            // Creates a new Variable with %name name. This object will be stored in the last created subcontext.
            // When this subcontext exit , the variable is invalid.
            NodeFunction* gms_var = new NodeFunction ( "Var" , NodeFunctionType::Normal , 2 ,
                [] ( std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                    
                    assert ( args.size() == 3 && "Arguments count provided invalid." ) ;
                    
                    NodeContext * ctxt = reinterpret_cast<NodeContext*>(args[0]) ;
                    if ( !ctxt ) {
                        std::cout << "Bad Context given !" << std::endl;
                        return NodeNull ;
                    }
                    
                    NodeVariableString * varname = reinterpret_cast<NodeVariableString*>(args[1]) ;
                    if ( !varname || varname->getType() != NodeType::Variable ||
                        varname->vartype != NodeVariableType::String ) {
                        std::cout << "Invalid %name argument ( !VariableString ) ." << std::endl;
                        return NodeNull ;
                    }
                    
                    NodeVariable * var = reinterpret_cast<NodeVariable*>(args[2]) ;
                    if ( !var || var->getType() != NodeType::Variable ) {
                        std::cout << "Invalid %expression argument ( !Variable ) ." << std::endl;
                        return NodeNull ;
                    }
                    
                    var->setName( varname->value ) ;
                    ctxt->addLocalVariable ( var ) ;
                    return NodeNull ;
            } , true ) ;
            ngms -> functions["Var"] = gms_var ;
            
            // Function : CreateProject %name -> Project
            // Creates a new project object.
            NodeFunction * gms_createproject = new NodeFunction ( "CreateProject" , NodeFunctionType::Normal , 1 ,
                [] ( std::vector<Node*>& args , WordPeeker & peeker ) -> Node* {
                
                    assert ( args.size() == 2 && "Given number of args is invalid." ) ;
                    
                    NodeContext * ctxt = reinterpret_cast<NodeContext*>(args[0]) ;
                    if ( !ctxt ) {
                        std::cout << "Bad Context given !" << std::endl;
                        return NodeNull ;
                    }
                    
                    NodeVariableString * varname = reinterpret_cast<NodeVariableString*>(args[1]) ;
                    if ( !varname || varname->getType() != NodeType::Variable ||
                        varname->vartype != NodeVariableType::String ) {
                        std::cout << "Invalid %name argument ( !VariableString ) ." << std::endl;
                        return NodeNull ;
                    }
                    
                    // Creates a new object with given name.
                    NodeProject * obj = new NodeProject ( varname->value ) ;
                    if ( !obj ) {
                        std::cout << "Couldn't create new project '" << varname->value << "'." << std::endl;
                        return NodeNull ;
                    }
                    
                    ctxt->addLocalVariable(obj) ;
                    return obj ;
            }) ;
            ngms -> functions["CreateProject"] = gms_createproject ;
        }
    }
}
