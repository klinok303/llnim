use llnim_rs::raylib_ref::RaylibRef;
use std::mem::size_of;
use llnim_rs::log_trace;
use raylib::ffi::TraceLogLevel;
use std::os::raw::{c_void, c_char};
use std::ptr;
use llnim_rs::env::Env;
use raylib::prelude::Color;

#[repr(C)]
struct Plug {
    size: usize,
    rref: RaylibRef,
}

static mut PLUG: Option<Box<Plug>> = None;

const MAX_CHARGE: i32 = 100;

#[no_mangle]
extern fn plug_init(rref: RaylibRef) {
    let mut plug = unsafe { PLUG.lock().unwrap() };
    *plug = Some(Box::new(Plug { size: size_of::<Plug>(), rref }));

    log_trace(TraceLogLevel::LOG_INFO, "-------------------");
    log_trace(TraceLogLevel::LOG_INFO, "Plugin Init success");
    log_trace(TraceLogLevel::LOG_INFO, "-------------------");
}

#[no_mangle]
unsafe extern fn plug_pre_reload() -> *mut c_void {
    PLUG.take().map_or_else(ptr::null_mut, |p| p as *mut Plug) as *mut c_void
}

#[no_mangle]
extern fn plug_post_reload(state: *mut c_void) {
    let mut plug = unsafe { PLUG.lock().unwrap() };
    *plug = unsafe { Some(Box::from_raw(state as *mut Plug)) };

    if let Some(plug_ref) = plug.as_mut() {
        if plug_ref.size < size_of::<Plug>() {
            log_trace(TraceLogLevel::LOG_INFO,
                      &*format!("Migrating plugin state schema {} -> {} bytes",
                                plug_ref.size, size_of::<Plug>()));
            plug_ref.size = size_of::<Plug>();
        }
    }
}

#[no_mangle]
unsafe extern fn plug_update(env: Env) {
    let plug = unsafe { PLUG.lock().unwrap() };
    let charge = ((MAX_CHARGE as f32 * (((env.time as f32).sin() / 5.0) + 1.0)) / 2.0) as i32;

    (plug.rref.clear_background)(Color::BEIGE.into());
    (plug.rref.draw_text)(charge.to_string().as_ptr() as *const c_char, 0, 0, 0,
                          Color::BLACK.into());
}