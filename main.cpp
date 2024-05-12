#include <iostream>
#include "dynamic_load.h"
#include "plug.h"

#include "api/raylib_ref.h"

#include "raylib.h"

int main(int argc, char const *argv[])
{
    if (argc < 1)
    {
        std::cout << "Usage: llnim <path to shared library>\n";
        return 1;
    }

    dl::SharedLibrary lib(argv[1]);

    plug_init = (void (*)(raylib_funcs))lib.Sym("plug_init");
    plug_pre_reload = (void* (*)())lib.Sym("plug_pre_reload");
    plug_post_reload = (void (*)(void*))lib.Sym("plug_pre_reload");
    plug_update = (void (*)(float, double))lib.Sym("plug_update");

    int factor = 100;

    raylib_funcs ref
    {
        GetScreenWidth, GetScreenHeight, ClearBackground, BeginDrawing,
        EndDrawing,
        DrawPixel, DrawLine, DrawLineEx, DrawLineStrip,
        DrawCircle, DrawCircleSector, DrawCircleSectorLines, DrawEllipse,
        DrawRectangle, DrawRectangleLines, DrawRectangleLinesEx, ColorFromHSV,
        ColorTint, ColorBrightness, ColorContrast, ColorAlpha, ColorAlphaBlend,
        GetColor, DrawText
    };

    InitWindow(16 * factor, 9 * factor, "LLNim");
    SetTargetFPS(240);

    plug_init(ref);

    while (!WindowShouldClose())
    {
#ifdef unix
        if (IsKeyPressed(KEY_R))
        {
            void *state = plug_pre_reload();

            lib = dl::SharedLibrary(argv[1]);

            plug_init = (void (*)(raylib_funcs))lib.Sym("plug_init");
            plug_pre_reload = (void* (*)())lib.Sym("plug_pre_reload");
            plug_post_reload = (void (*)(void*))lib.Sym("plug_pre_reload");
            plug_update = (void (*)(float, double))lib.Sym("plug_update");

            plug_post_reload(state);
        }
#endif

        plug_update(GetFrameTime(), GetTime());
    }

    CloseWindow();

    return 0;
}