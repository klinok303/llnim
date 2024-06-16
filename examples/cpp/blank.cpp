#include <cstddef>
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

extern "C" void plug_init(raylib_t ref)
{
    plug = (Plug*)plug_alloc(sizeof(*plug));

    plug->bg_col = LIGHTGRAY;
    plug->ref = ref;

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

extern "C" void plug_update(Env _env)
{
    (void)_env;
    plug->ref.clear_background(plug->bg_col);
}