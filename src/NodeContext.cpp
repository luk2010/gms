//
//  NodeContext.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "NodeContext.h"

namespace GMS
{
    NodeNamespace::NodeNamespace ( const std::string & name )
    : GMS::NodeWithName(name , NodeType::Namespace)
    {
        
    }
    
    Node * NodeNamespace::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        // Check if word is an object
        
        {
            auto it = objects.find ( word.content ) ;
            if ( it != objects.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        // Check if it's a variable.
        
        {
            auto it = variables.find ( word.content ) ;
            if ( it != variables.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        // Check if it's a function.
        
        {
            auto it = functions.find ( word.content ) ;
            if ( it != functions.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        return NodeNull ;
    }
    
    NodeSubContext::NodeSubContext ()
    : GMS::Node(NodeType::SubContext)
    {
        
    }
    
    NodeSubContext::~NodeSubContext()
    {
        if ( heapvariables.size() )
        {
            for ( auto it : heapvariables )
                delete it.second ;
        }
    }
    
    Node * NodeSubContext::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        // Check if it is in heap variables
        
        {
            auto it = heapvariables.find ( word.content ) ;
            if ( it != heapvariables.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        return NodeNull ;
    }
    
    void NodeSubContext::addVariable(GMS::NodeVariable *var)
    {
        assert( var && "[NodeContext::addVariable] Invalid Variable." ) ;
        heapvariables[var->getName()] = var ;
    }
    
    NodeContext::NodeContext ()
    : GMS::Node(NodeType::Context)
    {
        // Create the first subcontext. This subcontext is the one that englobe main
        // context heap.
        subcontexts.push_back( new NodeSubContext ) ;
    }
    
    Node * NodeContext::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        // If this is a String , we return a new heap variable.
        
        if ( word.type == WORD_TYPE_STRING )
        {
            static uint64_t strgen = 0 ;
            
            std::string sn = std::string("__str")+std::to_string(strgen) ;
            NodeVariable * str = new NodeVariableString ( sn , word.content ) ;
            addLocalVariable( str ) ;
            
            strgen ++ ;
            return str ;
        }
        
        // Check if it's a namespace
        
        {
            auto it = namespaces.find ( word.content ) ;
            if ( it != namespaces.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        // Check if in heap
        
        {
            auto it = heapvariables.find ( word.content ) ;
            if ( it != heapvariables.end() )
                return it->second->Analyse ( Context , peeker.next () , peeker ) ;
        }
        
        // Launch it to other subcontexts.
        
        for ( auto & ctxt : subcontexts )
        {
            Node * ret = ctxt -> Analyse ( Context , word , peeker ) ;
            if ( ret && ret->type != NodeType::None ) return ret ;
        }
        
        // See if it's not in the GMS namespace.
        
        {
            auto it = namespaces.find( "GMS" ) ;
            if ( it != namespaces.end() )
                return it->second->Analyse( Context, word, peeker ) ;
        }
        
        std::cout << "Word '" << word.content << "' as beginning a sentence is invalid." << std::endl;
        return NodeNull ;
    }
    
    void NodeContext::addLocalVariable(GMS::NodeVariable *var)
    {
        assert( var && "[NodeContext::addLocalVariable] Invalid Variable." ) ;
        assert( subcontexts.size() && "[NodeContext::addLocalVariable] Invalid subcontexts size." ) ;
        
        subcontexts.at(subcontexts.size() - 1)->addVariable( var ) ;
    }
}
