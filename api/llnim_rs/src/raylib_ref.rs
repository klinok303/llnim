use raylib::ffi;

/// This is a struct for containing raylib callbacks.
#[repr(C)]
#[derive(Debug)]
pub struct RaylibRef {
    pub get_screen_width: fn() -> i32,
    pub get_screen_height: fn() -> i32,

    pub clear_background: fn(ffi::Color),

    pub draw_pixel: fn(i32, i32, ffi::Color),
    pub draw_line: fn(i32, i32, i32, i32, ffi::Color),
    pub draw_line_ex: fn(ffi::Vector2, ffi::Vector2, f32, ffi::Color),
    pub draw_line_strip: fn(*mut ffi::Vector2, i32, ffi::Color),

    pub draw_circle: fn(i32, i32, f32, ffi::Color),
    pub draw_circle_sector: fn(ffi::Vector2, f32, f32, f32, i32, ffi::Color),
    pub draw_circle_sector_lines: fn(ffi::Vector2, f32, f32, f32, i32, ffi::Color),
    pub draw_ellipse: fn(i32, i32, f32, f32, ffi::Color),

    pub draw_rectangle: fn(i32, i32, i32, i32, ffi::Color),
    pub draw_rectangle_lines: fn(i32, i32, i32, i32, ffi::Color),
    pub draw_rectangle_lines_ex: fn(ffi::Rectangle, f32, ffi::Color),

    pub draw_text: fn(*const i8, i32, i32, i32, ffi::Color),

    pub begin_texture_mode: fn(ffi::RenderTexture2D),
    pub end_texture_mode: fn(),
    pub load_render_texture: fn(i32, i32) -> ffi::RenderTexture2D,
}