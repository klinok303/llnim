#include <stddef.h>
#include <math.h>
#include "raylib.h"
#include "../api/api.h"

static Plug *plug = NULL;

extern void plug_init(raylib_funcs ref)
{
    plug = plug_alloc();

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
    int h = plug->ref.get_screen_height();
    int rect = 100;

    plug->ref.clear_background(plug->bg_col);
    plug->ref.draw_rectangle((w - rect) * ((sinf(time) + 1) * 0.5f),
        (h * 0.5) - (rect * 0.5), rect, rect, DARKGRAY);

    plug->ref.end_drawing();
}