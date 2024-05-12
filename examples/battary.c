#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "raylib.h"
#include "../api/api.h"

static Plug *plug = NULL;

const int maxCharge = 100;

extern void plug_init(raylib_funcs ref)
{
    plug = malloc(sizeof(*plug));
    assert(plug != NULL && "Error: Bad plug alloc (buy more ram)");
    memset(plug, 0, sizeof(*plug));

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

extern void plug_update(float frame_time, double time)
{
    plug->ref.begin_drawing();

    int w = plug->ref.get_screen_width();

    int charge = (maxCharge * (sinf(time / 5) + 1)) / 2;
    char str[3];

    sprintf(str, "%d", charge);

    plug->ref.clear_background(plug->bg_col);
    plug->ref.draw_text(str, 0, 0, 50, GOLD);

    plug->ref.end_drawing();
}