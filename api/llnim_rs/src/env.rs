use raylib::ffi::{Sound, Wave};

#[repr(C)]
#[derive(Debug)]
pub struct Env {
    pub dt: f32,
    pub time: f64,
    pub screen_width: i32,
    pub screen_height: i32,
    pub play_sound: fn(Sound, Wave),
}