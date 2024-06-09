#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdint>

#include "api.h"

#include "Python.h"

void *plug_alloc(size_t size)
{
    void *p = malloc(size);
    assert(p != NULL && "Error: Bad plug alloc (buy more ram)");
    memset(p, 0, size);
    return p;
}

PyObject *data_to_PyByteArrayObject(void *data, size_t size)
{
    PyByteArrayObject *byte_array;
    byte_array->ob_alloc = size;
    byte_array->ob_bytes = (char*)data;
    return (PyObject*)byte_array;
}