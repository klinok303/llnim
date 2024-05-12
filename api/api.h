#ifndef API_H
#define API_H

#include "raylib.h"
#include "raylib_ref.h"

#ifdef __cplusplus
#define EXC extern "C"
#else
#define EXC
#endif

typedef struct 
{
    Color bg_col;
    raylib_funcs ref;
} Plug;

EXC Plug *plug_alloc();

#endif // API