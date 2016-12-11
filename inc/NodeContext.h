//
//  NodeContext.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef NodeContext_h
#define NodeContext_h

#include "Node.h"

#include "NodeObject.h"

namespace GMS
{
    // A Namespace is a structure that contains objects , variables , and functions.
    class NodeNamespace : public NodeWithName {
    public:
        
        std::map<std::string , NodeObject * > objects ;
        std::map<std::string , NodeVariable * > variables ;
        std::map<std::string , NodeFunction * > functions ;
        
        NodeNamespace ( const std::string & name ) ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
    };
    
    // A SubContext is a structure that represent a heap , virtually.
    class NodeSubContext : public Node {
    public:
        
        std::map<std::string , NodeVariable * > heapvariables ;
        
        NodeSubContext ( ) ;
        ~NodeSubContext () ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
        
        // Adds a Variable to this sub-context.
        void addVariable ( NodeVariable* var ) ;
    };
    
    // A Context holds namespaces , heap generated variables , and subcontext.
    class NodeContext : public Node {
    public:
        
        std::map<std::string , NodeNamespace * > namespaces ;
        std::map<std::string , NodeVariable * > heapvariables ;
        std::vector< NodeSubContext * > subcontexts ;
        
        NodeContext ( ) ;
        
        Node * Analyse ( Node * Context , const Word & word , WordPeeker & peeker ) ;
        
        // Adds to the last subcontext the given variable.
        void addLocalVariable ( NodeVariable * var ) ;
    };
}

#endif /* NodeContext_h */
