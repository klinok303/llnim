#ifndef RAYLIB_REF_H
#define RAYLIB_REF_H

#include "raylib.h"

typedef struct raylib_funcs
{
    int (*get_screen_width)(void);
    int (*get_screen_height)(void);

    void (*clear_background)(Color);

    /* TODO: not implemented --------------------------
    * void (*begin_mode_2d)(Camera2D);
    * void (*end_mode_2d)(void);
    * void (*begin_mode_3d)(Camera2D);
    * void (*begin_mode_3d)(void);
    * void (*begin_scissor_mode)(int, int, int, int);
    * -------------------------------------------------*/


    void (*draw_pixel)(int, int, Color);
    void (*draw_line)(int, int, int, int, Color);
    void (*draw_line_ex)(Vector2, Vector2, float, Color);
    void (*draw_line_strip)(Vector2*, int, Color);
    void (*draw_circle)(int, int, float, Color);
    void (*draw_circle_sector)(Vector2, float, float, float, int, Color);
    void (*draw_circle_sector_lines)(Vector2, float, float, float, int, Color);
    void (*draw_ellipse)(int, int, float, float, Color);
    void (*draw_rectangle)(int, int, int, int, Color);
    void (*draw_rectangle_lines)(int, int, int, int, Color);
    void (*draw_rectangle_lines_ex)(Rectangle, float, Color);

    Color (*color_from_hsv)(float, float, float);
    Color (*color_tint)(Color, Color);
    Color (*color_brightness)(Color, float);
    Color (*color_contrast)(Color, float);
    Color (*color_alpha)(Color, float);
    Color (*color_alpha_blend)(Color, Color, Color);
    Color (*get_color)(unsigned int);

    void (*draw_text)(const char*, int, int, int, Color);

    void (*begin_texture_mode)(RenderTexture2D);
    void (*end_texture_mode)(void);
    RenderTexture2D (*load_render_texture)(int, int);
} raylib_t;

#endif // RAYLIB_REF