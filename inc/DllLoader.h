//
//  DllLoader.h
//  GMS
//
//  Created by Jacques Tronconi on 04/12/2016.
//  Copyright © 2016 Atlanti's Corporation. All rights reserved.
//

#ifndef DllLoader_h
#define DllLoader_h

#include "Utils.h"
#include "Bundle.h"

#if defined(__WINDOWS__)
#   define DYNLIB_HANDLE hInstance
#   define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#   define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#   define DYNLIB_UNLOAD( a ) FreeLibrary( a )
#   define DYNLIB_EXTENSION "dll"
#   define DYNLIB_LASTERROR dlerror

struct HINSTANCE__;
typedef struct HINSTANCE__ * hInstance;

/* We provide custom dlerror for Windows(tm).
 * https://mail.python.org/pipermail//pypy-commit/2012-October/066804.html
 */
static const char *dlerror(void)
{
    static char buf[32];
    DWORD dw = GetLastError();
    if (dw == 0)
        return NULL;
    sprintf(buf, "error 0x%x", (unsigned int)dw);
    return buf;
}

#else
#  if defined(__OSX__) || defined (__APPLE__)
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a , RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "dylib"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>
#
#  else
#
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a , RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "so"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>
#
#  endif

#endif

namespace GMS
{
    class DllLoader
    {
    public:
        
        DllLoader ( const std::string & path ) ;
        ~DllLoader () ;
        
        bool load ( ) ;
        Bundle * getBundle ( ) ;
        
    protected:
        
        std::string path ;
        DYNLIB_HANDLE handle ;
        Bundle * bundle ;
    };
}

#endif /* DllLoader_h */
