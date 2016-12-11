//
//  NodeFunction.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "NodeFunction.h"
#include "NodeVariable.h"

namespace GMS
{
    NodeFunction::NodeFunction ( const std::string & n , const NodeFunctionType & t ,
                                uint8_t c , Node * (*f) ( std::vector<Node*> & args , WordPeeker& ) ,
                                bool fn )
    : GMS::NodeWithName(n, NodeType::Function) , functype(t) , usefakename(fn)
    , argc(c) , func(f)
    {
        
    }
    
    NodeFunction::~NodeFunction()
    {
        
    }
    
    Node * NodeFunction::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        if ( functype == NodeFunctionType::Normal )
        {
            // Here , first word is the first arg of the function. BUT , if we do not have any args , we must
            // undo the peeker to let the interpreter interprete next word as a new sentence.
            peeker.undo () ;
            
            std::vector < Node* > tmpargs ;
            tmpargs . push_back ( Context ) ;
            
            for ( uint8_t i = 0 ; i < argc ; i++ )
            {
                if ( usefakename )
                {
                    Word wnext = peeker.next() ;
                    Node * arg = Context -> Analyse ( Context , wnext , peeker ) ;
                    assert ( arg && "[NodeFunction::Analyse] Invalid return node." ) ;
                    
                    if ( arg == NodeNull ) {
                        arg = new NodeVariableString ( "" , wnext.content ) ;
                    }
                        
                    tmpargs.push_back ( arg ) ;
                }
                
                else
                {
                    Node * arg = Context -> Analyse ( Context , peeker.next() , peeker ) ;
                    assert ( arg && "[NodeFunction::Analyse] Invalid return node." ) ;
                    tmpargs.push_back(arg) ;
                }
            }
            
            if ( usefakename ) {
                Node * ret = callFunction ( tmpargs , peeker ) ;
                
                for ( auto it = tmpargs.begin()+1 ; it != tmpargs.end() ; it++ ) {
                    if ( (*it)->getType() == NodeType::Variable ) {
                        NodeVariable * v = reinterpret_cast<NodeVariable*>(*it) ;
                        if ( v->vartype == NodeVariableType::String && v->getName().empty() ) {
                            delete v ;
                        }
                    }
                }
                
                return ret ;
            }
            
            else {
                return callFunction ( tmpargs , peeker ) ;
            }
        }
        
        else if ( functype == NodeFunctionType::Variadic )
        {
            // For a variadic function , the function has to call the peeker to get other args, depending
            // on its own implementation.
            peeker.undo() ;
            
            std::vector < Node * > tmpargs ;
            tmpargs.push_back( Context ) ;
            
            return callFunction ( tmpargs , peeker ) ;
        }
        
        return NodeNull ;
    }
    
    Node * NodeFunction::callFunction(std::vector<Node *> &args, GMS::WordPeeker &peeker)
    {
        assert( func && "[NodeFunction:callFunction] Invalid Function provided." ) ;
        return func ( args , peeker ) ;
    }
    
    NodeFunctionMember::NodeFunctionMember ( const std::string & n , const NodeFunctionType & t ,
                                            uint8_t argc , Node * (*f) ( Node * owner , std::vector<Node*> & args , WordPeeker & peeker ) ,
                                            Node * c , bool considerfakename )
    : GMS::NodeFunction(n, t, argc, nullptr, considerfakename) , owner(c) , memberfunc(f)
    {
        assert( c && "[NodeFunctionMember:NodeFunctionMember] Given Owner is invalid." ) ;
    }
    
    NodeFunctionMember::~NodeFunctionMember()
    {
        
    }
    
    Node * NodeFunctionMember::callFunction(std::vector<Node *> &args, GMS::WordPeeker &peeker)
    {
        assert( memberfunc && "[NodeFunctionMember:callFunction] Invalid Function provided." ) ;
        assert( owner && "[NodeFunctionMember:callFunction] Invalid owner object." ) ;
        return memberfunc ( owner , args , peeker ) ;
    }
}
