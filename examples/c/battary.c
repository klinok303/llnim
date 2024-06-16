#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "raylib.h"
#include "../../api/raylib_ref.h"
#include "../../api/api.h"
#include "../../api/env.h"

typedef struct 
{
    Color bg_col;
    raylib_t ref;
} Plug;

static Plug *plug = NULL;

const int maxCharge = 100;

extern void plug_init(raylib_t ref)
{
    plug = plug_alloc(sizeof(*plug));

    plug->bg_col = LIGHTGRAY;
    plug->ref = ref;

    TraceLog(LOG_INFO, "--------------------------");
    TraceLog(LOG_INFO, "Plugin Init success");
    TraceLog(LOG_INFO, "--------------------------");
}

extern void *plug_pre_reload()
{
    return plug;
}

extern void plug_post_reload(void *state)
{
    plug = state;
}

extern void plug_update(Env env)
{
    int charge = (maxCharge * (sinf(env.time / 5) + 1)) / 2;
    char str[6];

    snprintf(str, sizeof(str), "%d", charge);

    plug->ref.clear_background(plug->bg_col);
    plug->ref.draw_text(str, 0, 0, 50, GOLD);
}