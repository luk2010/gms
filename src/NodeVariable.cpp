//
//  NodeVariable.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "NodeVariable.h"

namespace GMS
{
    NodeVariable::NodeVariable ( const std::string & name , const NodeVariableType & t )
    : GMS::NodeWithName(name , NodeType::Variable) , vartype(t)
    {
        
    }
    
    NodeVariable::NodeVariable ( const std::string & name , const NodeType & nt , const NodeVariableType & vt )
    : GMS::NodeWithName(name , nt) , vartype(vt)
    {
        
    }
    
    Node * NodeVariable::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        return NodeNull ;
    }
    
    NodeVariableString::NodeVariableString ( const std::string & name , const std::string & cont )
    : GMS::NodeVariable(name , NodeVariableType::String) , value(cont)
    {
        
    }
    
    Node * NodeVariableString::Analyse(GMS::Node *Context, const GMS::Word &word, GMS::WordPeeker &peeker)
    {
        // See if the word is an embedded function.
        
        if ( word.content == "Get" )
            return this ;
        
        if ( word.content == "Append" )
        {
            Node * strvalue = Context -> Analyse ( Context , peeker.next() , peeker ) ;
            
            if ( strvalue->type != NodeType::Variable )
            {
                std::cout << "Invalid Sentence given after Word '" << word.content << "'." << std::endl;
                return NodeNull ;
            }
            
            NodeVariable * strvar = reinterpret_cast < NodeVariable* > ( strvalue ) ;
            
            if ( strvar->vartype != NodeVariableType::String )
            {
                std::cout << "Invalid Variable given after Word '" << word.content << "'." << std::endl;
                return NodeNull ;
            }
            
            NodeVariableString * strstr = reinterpret_cast < NodeVariableString * > ( strvar ) ;
            value.insert ( value.end() , strstr->value.begin() , strstr->value.end() ) ;
            return NodeNull ;
        }
        
        if ( word.content == "Clear" )
        {
            value.clear () ;
            return NodeNull ;
        }
        
        std::cout << "Invalid Word '" << word.content << "' after VariableString." << std::endl;
        return NodeNull ;
    }
}
