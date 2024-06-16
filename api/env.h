#ifndef ENV_H
#define ENV_H

#include <raylib.h>

typedef struct Enviroment
{
    float dt;
    double time;
    int screenWidth;
    int screenHeight;
    void (*play_sound)(Sound sound, Wave wave);
} Env;

#endif // ENV