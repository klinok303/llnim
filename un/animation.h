#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct Key { float from, to, dur; } key_t;

typedef struct Animaton
{
    size_t i;
    float dur;
    bool isLoop;
} anim_t;

extern "C" float anim_val(anim_t *a, key_t *keys, size_t size);
extern "C" void anim_update(anim_t *a, key_t *keys, size_t size, float dt);

#endif // ANIMATION