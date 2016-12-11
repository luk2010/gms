//
//  WordPeeker.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef WordPeeker_h
#define WordPeeker_h

#include "Utils.h"

namespace GMS
{
    
#define WORD_TYPE_TEXT      1
#define WORD_TYPE_STRING    2
#define WORD_TYPE_COMMENT   3
    
    struct Word
    {
        uint8_t type ;
        std::string content ;
    };
    
    class WordPeeker
    {
    public:
        
        WordPeeker ( const std::string & content ) ;
        
        // Proceeds to the reading of the given content.
        // Separate every words , ignore comments .
        // Returns the number of word discovered.
        size_t proceed () ;
        
        Word next () ;
        void undo () ;
        
    protected:
        
        std::string Content ;
        
        std::vector < Word > Words ;
        std::vector < Word > Comments ;
        
        Word CurrentWord ;
        size_t CurrentIndex ;
    };
}

#endif /* WordPeeker_h */
