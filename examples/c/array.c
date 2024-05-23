#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "raylib.h"

#include "../../api/raylib_ref.h"
#include "../../api/api.h"

typedef struct 
{
    size_t size;
    raylib_t ref;
} Plug;

static Plug *plug = NULL;

extern void plug_init(raylib_t ref)
{
    plug = plug_alloc(sizeof(*plug));
    plug->size = sizeof(*plug);

    // plug->screen = ref.load_render_texture(RENDER_WIDTH, RENDER_HEIGHT);

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
    if (plug->size < sizeof(*plug))
    {
        TraceLog(LOG_INFO, "Migrating plugin state schema %zu -> %zu bytes",
            plug->size, sizeof(*plug));

        plug = realloc(plug, sizeof(*plug));
        plug->size = sizeof(*plug);
    }
}

static void render(float time, int rect, float pad_mult)
{
    int pad = rect * pad_mult;

    int w = plug->ref.get_screen_width();

    plug->ref.clear_background(LIGHTGRAY);

    for (size_t i = 0; i < 5; i++)
    {
        plug->ref.draw_rectangle((w - rect) * ((sinf(time) + 1) * 0.5f), 
            i * (rect + pad), rect, rect, DARKGRAY);
    }
}

extern void plug_update(float frame_time, double time)
{
    render(time, 100, 0.25f);
}