//
//  main.cpp
//  GMS
//
//  Created by Jacques Tronconi on 01/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#include "Interpreter.h"

int main(int argc, const char * argv[]) {
    
    std::cout << "GMS Build System." << std::endl;
    std::cout << "Version : " << GMS::CurrentVersion << std::endl;
    
    if ( argc <= 1 )
    {
        std::cout << "No filepath specified. Please type one : " << std::endl;
        std::cout << ":> " ;
        
        std::cout.flush() ;
        
        std::string filepath ;
        char c = std::cin.get() ; while ( c != '\n' ) { filepath.push_back(c) ; c = std::cin.get() ; }
        std::cout << "Filepath = " << filepath << std::endl ;
        
        if ( filepath.empty() )
        {
            std::cout << "Filepath is empty." << std::endl;
            exit (0) ;
        }
        
        std::cout << "Getting '" << filepath << "' content." << std::endl;
        
        std::string filecontent ;
        std::ifstream fstream ( filepath , std::ios::ate ) ;
        if ( !fstream )
        {
            std::cout << "Can't open file '" << filepath << "'." << std::endl;
            exit (0) ;
        }
        
        size_t fsize = fstream.tellg() ;
        if ( fsize == 0 )
        {
            std::cout << "File '" << filepath << "' is empty." << std::endl;
            exit (0) ;
        }
        
        filecontent.reserve(fsize) ;
        fstream.seekg(std::ios::beg) ;
        
        while ( !fstream.eof() )
            filecontent.push_back( fstream.get() ) ;
        
        fstream.close() ;
        std::cout << "File content is " << filecontent.size() << " long." << std::endl ;
        
        std::cout << "Peeking Words." << std::endl;
        
        GMS::WordPeeker wordpeeker ( filecontent ) ;
        size_t words = wordpeeker.proceed () ;
        
        std::cout << "Peeked " << words << " Words." << std::endl;
        
        std::cout << "Creating Interpreter." << std::endl;
        
        GMS::Interpreter interpreter ( &wordpeeker ) ;
        interpreter.interprete() ;
    }
    
    return 0;
}
