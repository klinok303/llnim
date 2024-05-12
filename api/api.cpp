#include <cstdlib>
#include <cassert>
#include <cstring>
#include "api.h"

Plug *plug_alloc()
{
    Plug *p = (Plug *)malloc(sizeof(*p));
    assert(p != NULL && "Error: Bad plug alloc (buy more ram)");
    memset(p, 0, sizeof(*p));
    return p;
}