#include "dynamic_load.h"
using namespace dl;

#ifdef _WIN32
    #include <cassert>
    #include <windows.h>
#endif // _WIN32

#ifdef unix
    #include <iostream>
    #include <cstdlib>
    #include <dlfcn.h> // dlopen, dlsym, dlclose
#endif // unix

SharedLibrary::SharedLibrary(const char *filename)
{
    #ifdef _WIN32
        this->handle = LoadLibraryA(filename);

        assert(this->handle && "Error: library not found");
    #endif // _WIN32

    #ifdef unix
        char *err;
        this->handle = dlopen(filename, RTLD_NOW);

        if ((err = dlerror()) == NULL)
        {
            std::cerr << "Error: " << err << "\n";
            abort();
        }
    #endif // unix
}

void *SharedLibrary::Sym(const char *symbol)
{
    #ifdef _WIN32
        return (void*)GetProcAddress((HMODULE)handle, symbol);
    #endif // _WIN32
    
    #ifdef unix
        return dlsym(dyn_handle, symbol);
    #endif // unix
}

SharedLibrary::~SharedLibrary()
{
    #ifdef _WIN32
        int err = FreeLibrary((HMODULE)this->handle);
        assert(err && "Error: bad dealloc library");
    #endif // _WIN32
    
    #ifdef unix
        char *err;
        dlclose(this->handle);

        if ((err = dlerror()) != NULL)
        {
            std::cerr << "Error: " << err << "\n";
            abort();
        }
    #endif // unix
}