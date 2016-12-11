//
//  WordPeeker.cpp
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "WordPeeker.h"

namespace GMS
{
    WordPeeker::WordPeeker ( const std::string & content )
    : Content(content)
    {
        
    }
    
    size_t WordPeeker::proceed()
    {
        Word current ;
        
        for ( auto it = Content.begin() ; it != Content.end() ; it ++ )
        {
            if ( (*it) == '/' && *(it+1) == '/' && current.content.empty() )
            {
                // This is a comment so just ignore untill next '\n' .
                Word comment ; comment.type = WORD_TYPE_COMMENT ;
                it ++ ; it ++ ;
                while ( *it != '\n' ) {
                    comment.content.push_back(*it) ;
                    it ++ ;
                }
                
                Comments.push_back(comment) ;
                continue ;
            }
            
            if ( std::isspace(*it) && !current.content.empty() )
            {
                // We reach an espace and current word is not empty so create a new one and
                // register this one.
                Words.push_back(current) ;
                current.type = 0 ;
                current.content.clear() ;
                continue ;
            }
            
            if ( std::isspace(*it) && current.content.empty() )
                continue ;
            
            if ( !std::isspace(*it) && current.content.empty() )
            {
                // Check the character to see if we have a Text or a String.
                if ( *it == '"' )
                {
                    // Fill the Word with the inner String .
                    // We have set here that the String do not contains the '"' .
                    current.type = WORD_TYPE_STRING ; it ++ ;
                    
                    while ( *it != '"' ) {
                        current.content.push_back(*it) ;
                        it ++ ;
                    }
                    
                    // We have our string , just create new Word.
                    Words.push_back(current) ;
                    current.type = 0 ;
                    current.content.clear() ;
                    continue ;
                }
                
                // If this is not a String , this is a Text . Thus , append the character
                // and wait for loop.
                current.type = WORD_TYPE_TEXT ;
                current.content.push_back(*it) ;
                continue ;
            }
            
            if ( !std::isspace(*it) && !current.content.empty() )
            {
                // We are in a Text , so append it.
                current.content.push_back(*it) ;
                continue ;
            }
        }
        
        if ( Words.size() ) {
            CurrentWord = Words.at(0) ;
            CurrentIndex = 0 ;
        }
        
        return Words.size() ;
    }
    
    Word WordPeeker::next()
    {
        Word ret = CurrentWord ;
        CurrentIndex ++ ;
        
        if ( CurrentIndex < Words.size() )
            CurrentWord = Words.at(CurrentIndex) ;
        else
            CurrentWord = { 0 , "" } ;
        
        return ret ;
    }
    
    void WordPeeker::undo()
    {
        if ( CurrentIndex > 0 )
        {
            CurrentIndex -- ;
            CurrentWord = Words.at(CurrentIndex) ;
        }
    }
}
