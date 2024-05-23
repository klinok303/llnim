#ifndef PLUG_H
#define PLUG_H

#include <cstddef>

#include "api/raylib_ref.h"

#include "Python.h"

void (*plug_init)(raylib_t) = NULL;
void *(*plug_pre_reload)(void) = NULL;
void (*plug_post_reload)(void*) = NULL;
void (*plug_update)(float, double) = NULL;

#endif // PLUG