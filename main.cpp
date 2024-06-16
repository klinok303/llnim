#include "dynamic_load.h"
#include "plug.h"

#include "api/raylib_ref.h"
#include "api/env.h"

#include "raylib.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <string>

#define RENDER_WIDTH 1600
#define RENDER_HEIGHT 900
#define RENDER_FPS 24
#define RENDER_DT 1.0f/RENDER_FPS
#define RENDER_LEN 5

void FfmpegSendFrameFlipped(std::ofstream &file, void *data, size_t width, size_t height)
{
    if (!file.is_open())
    {
        TraceLog(LOG_ERROR, "Error: File is not open.");
        return;
    }

    for (size_t y = height; y > 0; --y)
    {
        uint32_t* address = reinterpret_cast<uint32_t*>(data) + (y - 1) * width;
        file.write(reinterpret_cast<char*>(address), sizeof(uint32_t) * width);
    }

    TraceLog(LOG_DEBUG, "Data has been written to file.");
}

void FfmpegCombine(int width, int height, int fps, const std::string& path) {
    std::string cmd = "ffmpeg -loglevel verbose -y -f rawvideo -pix_fmt rgba -s " +
        std::to_string(width) + "x" + std::to_string(height) + " -r " +
        std::to_string(fps) + " -i " + path +
        " -c:v libx264 -vb 2500k -c:a aac -ab 200k -pix_fmt yuv420p output.mp4";

    int result = system(cmd.c_str());

    if (result == 0) { TraceLog(LOG_INFO, "FFmpeg command executed successfully."); }
    else { TraceLog(LOG_ERROR, "FFmpeg command failed."); }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        TraceLog(LOG_ERROR, "Usage: llnim <path to shared library (plugin)>");
        return -1;
    }

    dl::SharedLibrary lib(argv[1]);

    plug_init = (void (*)(raylib_t))lib.Sym("plug_init");
    plug_pre_reload = (void* (*)())lib.Sym("plug_pre_reload");
    plug_post_reload = (void (*)(void*))lib.Sym("plug_pre_reload");
    plug_update = (void (*)(Env))lib.Sym("plug_update");

    int factor = 100;

    raylib_t ref
    {
        ClearBackground, DrawPixel, DrawLine, DrawLineEx, DrawLineStrip,
        DrawCircle, DrawCircleSector, DrawCircleSectorLines, DrawEllipse,
        DrawRectangle, DrawRectangleLines, DrawRectangleLinesEx, DrawText,
        BeginTextureMode, EndTextureMode
    };

    InitWindow(16 * factor, 9 * factor, "LLNim");
    SetTargetFPS(240);

    plug_init(ref);

    bool isRendering = false;

    double ffmpeg_render_timer = 0;

    RenderTexture2D screen = LoadRenderTexture(16 * factor, 9 * factor);

    std::ofstream file("temp_frames.raw", std::ios::out | std::ios::binary);

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
            plug_update = (void (*)(Env))lib.Sym("plug_update");

            plug_post_reload(state);
        }
#endif

        BeginDrawing();

        if (!isRendering)
        {
            isRendering = IsKeyPressed(KEY_R);
            plug_update({GetFrameTime(), GetTime(), GetScreenWidth(), GetScreenHeight(), NULL});
        }
        else
        {
            BeginTextureMode(screen);
                plug_update({ .dt=RENDER_DT, .time=ffmpeg_render_timer, .screenWidth=GetScreenWidth(), .screenHeight=GetScreenHeight(), .play_sound=NULL});
            EndTextureMode();
            ffmpeg_render_timer += RENDER_DT;

            Image img = LoadImageFromTexture(screen.texture);
            FfmpegSendFrameFlipped(file, img.data, 16 * factor, 9 * factor);
            UnloadImage(img);

            if (ffmpeg_render_timer >= RENDER_LEN)
            {
                FfmpegCombine(RENDER_WIDTH, RENDER_HEIGHT, RENDER_FPS, "temp_frames.raw");
                isRendering = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}