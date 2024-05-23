#include "dynamic_load.h"
#include "plug.h"

#include "api/raylib_ref.h"

#include "raylib.h"
#include "Python.h"

#include <iostream>

#define RENDER_WIDTH 1600
#define RENDER_HEIGHT 900
#define RENDER_FPS 24
#define RENDER_DT 1.0f/RENDER_FPS
#define RENDER_LEN 5

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        TraceLog(LOG_ERROR, "programme Usage: llnim <path to shared library (plugin)>");
        return -1;
    }

    dl::SharedLibrary lib(argv[1]);

    plug_init = (void (*)(raylib_t))lib.Sym("plug_init");
    plug_pre_reload = (void* (*)())lib.Sym("plug_pre_reload");
    plug_post_reload = (void (*)(void*))lib.Sym("plug_pre_reload");
    plug_update = (void (*)(float, double))lib.Sym("plug_update");

    Py_Initialize();

    int factor = 100;

    PyObject *ffmpeg = PyImport_Import(PyUnicode_FromString("scripts.ffmpeg"));
    if (!ffmpeg) 
    {
        TraceLog(LOG_ERROR, "ffmpeg script not found");
        return -2;
    }

    PyObject *ffmpeg_process = NULL;

    raylib_t ref
    {
        GetScreenWidth, GetScreenHeight, ClearBackground,
        DrawPixel, DrawLine, DrawLineEx, DrawLineStrip,
        DrawCircle, DrawCircleSector, DrawCircleSectorLines, DrawEllipse,
        DrawRectangle, DrawRectangleLines, DrawRectangleLinesEx, ColorFromHSV,
        ColorTint, ColorBrightness, ColorContrast, ColorAlpha, ColorAlphaBlend,
        GetColor, DrawText, BeginTextureMode, EndTextureMode, LoadRenderTexture
    };

    InitWindow(16 * factor, 9 * factor, "LLNim");
    SetTargetFPS(240);

    plug_init(ref);

    bool isRendering = false;

    double ffmpeg_render_timer = 0;

    RenderTexture2D screen = LoadRenderTexture(16 * factor, 9 * factor);

    while (!WindowShouldClose())
    {
#ifdef unix
        if (IsKeyPressed(KEY_Q))
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

        BeginDrawing();

        if (ffmpeg_process == NULL)
        {
            if (IsKeyPressed(KEY_R))
            {
                PyObject* srf = PyObject_GetAttrString(ffmpeg,
                    "ffmpeg_start_rendering");

                PyObject* srArgs = PyTuple_Pack(3,
                    PyLong_FromLong(16 * factor), PyLong_FromLong(9 * factor),
                    PyLong_FromLong(RENDER_FPS));

                ffmpeg_process = PyObject_CallObject(srf, srArgs);

                Py_DECREF(srArgs);
                Py_DECREF(srf);
            }
            plug_update(GetFrameTime(), GetTime());
        }
        else
        {
            BeginTextureMode(screen);
                plug_update(RENDER_DT, ffmpeg_render_timer);
            EndTextureMode();
            ffmpeg_render_timer += RENDER_DT;

            Image img = LoadImageFromTexture(screen.texture);
            PyObject* ffmpeg_send_frame_flipped = PyObject_GetAttrString(ffmpeg,
                "ffmpeg_send_frame_flipped");

            PyObject* fsffArgs = PyTuple_Pack(4, ffmpeg_process, 
                PyBytes_FromStringAndSize((const char*)img.data,
                    img.width*img.height*sizeof(int)),
                PyLong_FromLong(16 * factor), PyLong_FromLong(9 * factor));
            
            PyObject_CallObject(ffmpeg_send_frame_flipped, fsffArgs);

            Py_DECREF(ffmpeg_send_frame_flipped);
            Py_DECREF(fsffArgs);
            UnloadImage(img);

            if (ffmpeg_render_timer >= RENDER_LEN)
            {
                PyObject* ffmpeg_end_rendering = PyObject_GetAttrString(ffmpeg,
                    "ffmpeg_end_rendering");
                PyObject* ferArgs = PyTuple_Pack(1, ffmpeg_process);

                PyObject_CallObject(ffmpeg_end_rendering, ferArgs);
                ffmpeg_process = NULL;

                Py_DECREF(ferArgs);
                Py_DECREF(ffmpeg_end_rendering);
            }
        }

        EndDrawing();
    }

    std::cout << "End";

    if (ffmpeg != NULL) 
    {
        Py_DECREF(ffmpeg);
    }

    Py_Finalize();
    CloseWindow();

    return 0;
}