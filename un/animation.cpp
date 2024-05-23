#include <cstring>
#include <cassert>
#include "animation.h"
#include "raymath.h"

extern "C" void anim_update(anim_t *a, key_t *keys, size_t size, float dt)
{
    if (a->i >= size) 
    {
        if (a->isLoop)
        {
            assert(size > 0);
            a->i = 0;
            a->isLoop = true;
        }
        else return;
    }
    key_t *kf = &keys[a->i]

    a->dur += dt;

    while (a->dur >= kf->dur && a->i + 1 < size) 
    {
        a->dur -= kf->dur;
        a->i += 1;
        kf = &keys[a->i]
    }
}

extern "C" float anim_val(anim_t *a, key_t *keys, size_t size)
{
    if (a->i >= size) { return keys[size - 1].to; }
    key_t *kf = &keys[a->i];

    return Lerp(kf->from, kf->to, a->dur/kf->dur);
}