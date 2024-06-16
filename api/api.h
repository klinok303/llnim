#ifndef API_H
#define API_H

#ifdef __cplusplus
#define EXC extern "C"
#else
#define EXC
#endif

EXC void *plug_alloc(size_t size);

#endif // API