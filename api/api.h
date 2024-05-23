#ifndef API_H
#define API_H

#include "Python.h"

#ifdef __cplusplus
#define EXC extern "C"
#else
#define EXC
#endif

EXC void *plug_alloc(size_t size);

EXC PyObject *data_to_PyByteArrayObject(void *data, size_t size);

#endif // API