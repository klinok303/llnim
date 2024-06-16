#include <cstddef>
#include <cmath>
#include "raylib.h"
#include "../../api/raylib_ref.h"
#include "../../api/api.h"
#include "../../api/animation.h"
#include "../../api/easings.h"
#include "../../api/env.h"

typedef struct 
{
    Color bg_col;
    raylib_t ref;
    anim_t animation;
} Plug;

static Plug *plug = NULL;

extern "C" void plug_init(raylib_t ref)
{
    plug = (Plug*)plug_alloc(sizeof(*plug));

    plug->bg_col = RED;
    plug->ref = ref;
    plug->animation.isLoop = true;

    TraceLog(LOG_INFO, "--------------------------");
    TraceLog(LOG_INFO, "Plugin Init success");
    TraceLog(LOG_INFO, "--------------------------");
}

extern "C" void *plug_pre_reload()
{
    return (void*)plug;
}

extern "C" void plug_post_reload(void *state)
{
    plug = (Plug*)state;
}

extern "C" void plug_update(Env env)
{
    key_t keyframes[] = {
        { .from = 0.0f, .to = 1.0f, .dur = 1.0f },
        { .from = 1.0f, .to = 0.0f, .dur = 1.0f }
    };

    size_t keyframes_count = 3;

    plug->ref.clear_background(plug->bg_col);

    anim_update(&plug->animation, keyframes, keyframes_count, env.dt);

    float t = anim_val(plug->animation, keyframes, keyframes_count);

    int rect = 100;

    plug->ref.draw_rectangle(EASE_IN_OUT_SINE(t) * (env.screenWidth - rect), 0.0f, rect, rect, DARKGRAY);
}