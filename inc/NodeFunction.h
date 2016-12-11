//
//  NodeFunction.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef NodeFunction_h
#define NodeFunction_h

#include "Node.h"

namespace GMS
{
    enum class NodeFunctionType
    {
        Normal , Variadic
    };
    
    // A Function is a structure with a name , a function type ( normal , variadic ) , number of argument
    // to take , and a pointer to the real function. A pointer to GMS Function is a function that take
    // a vector of Node as arguments , and return a node as value.
    class NodeFunction : public NodeWithName {
        
    protected:
        
        NodeFunctionType functype ;
        uint8_t argc ;
        Node * (*func) ( std::vector<Node*> & args , WordPeeker & peeker ) ;
        bool usefakename ; // This is true when you want to convert fake names to string.
        
    public:
        
        NodeFunction ( const std::string & n , const NodeFunctionType & t ,
                      uint8_t argc , Node * (*f) ( std::vector<Node*> & args , WordPeeker & peeker ) ,
                      bool considerfakename = false ) ;
        
        virtual ~NodeFunction () ;
        
        virtual Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
        
        virtual Node * callFunction ( std::vector<Node*> & args , WordPeeker & peeker ) ;
    };
    
    // A Member Function is a Function which belongs to a given Object. This Function should be stored
    // only in the Object.
    class NodeFunctionMember : public NodeFunction {
        
    public:
        
        Node * owner ; // Represents the Object owning this function.
        Node * (* memberfunc) ( Node* owner , std::vector<Node*> & args , WordPeeker & peeker ) ;
        
    public:
        
        NodeFunctionMember ( const std::string & n , const NodeFunctionType & t ,
                            uint8_t argc , Node * (*f) ( Node* owner , std::vector<Node*> & args , WordPeeker & peeker ) ,
                            Node * c , bool considerfakename = false ) ;
        
        virtual ~NodeFunctionMember ( ) ;
        
        virtual Node * callFunction ( std::vector<Node*> & args , WordPeeker & peeker ) ;
    } ;
}

#endif /* NodeFunction_h */
