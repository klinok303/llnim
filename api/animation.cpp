#include <cstring>
#include <cassert>
#include "animation.h"
#include "raymath.h"

void anim_update(anim_t *a, key_t *keys, size_t size, float dt)
{
    if (a->i >= size) 
    {
        if (a->isLoop)
        {
            a->i = 0;
            a->dur = 0.0f;
        }
        else return;
    }

    a->dur += dt;

    while (a->i < size && a->dur >= keys[a->i].dur) 
    {
        a->dur -= keys[a->i].dur;
        a->i += 1;
    }
}

float anim_val(anim_t a, key_t *keys, size_t size)
{
    assert(size > 0);
    if (a.i >= size) { return keys[size - 1].to; }
    key_t *kf = &keys[a.i];

    return Lerp(kf->from, kf->to, a.dur/kf->dur);
}