#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdint>

#include "api.h"

void *plug_alloc(size_t size)
{
    void *p = malloc(size);
    assert(p != NULL && "Error: Bad plug alloc (buy more ram)");
    memset(p, 0, size);
    return p;
}