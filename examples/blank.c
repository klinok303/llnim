#include <stddef.h>
#include "raylib.h"
#include "..\api\api.h"

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

    plug->ref.clear_background(plug->bg_col);
    
    plug->ref.end_drawing();
}