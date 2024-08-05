use llnim_rs::raylib_ref::RaylibRef;
use llnim_rs::animation::{Animation, Key};
use std::mem::size_of;
use llnim_rs::log_trace;
use std::os::raw::c_void;
use raylib::ffi::TraceLogLevel;
use std::ptr;
use llnim_rs::env::Env;
use raylib::prelude::Color;

#[repr(C)]
struct Plug {
    size: usize,
    rref: RaylibRef,
    anim: Animation,
}

static mut PLUG: Option<Box<Plug>> = None;

#[no_mangle]
extern fn plug_init(rref: RaylibRef) {
    let mut plug = unsafe { PLUG.lock().unwrap() };
    *plug = Some(Box::new(Plug { size: size_of::<Plug>(), rref, anim: Animation {
        i: 0, dur: 0.0, is_loop: true} }));

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
    let keys: [Key; 2] = [
        Key { from: 0.0, to: 1.0, dur: 1.0 },
        Key { from: 1.0, to: 1.0, dur: 1.0 },
    ];

    let mut plug = unsafe { PLUG.lock().unwrap() };

    (plug.rref.clear_background)(Color::BROWN.into());

    plug.anim.update(&keys, env.dt);

    let v = plug.anim.val(&keys);
    let rect = 100;

    (plug.rref.draw_rectangle)((env.screen_width - rect) * (((env.time as f32).sin() + 1.0)
        * 0.5) as i32, rect, rect, rect, Color::DARKBLUE.into());
    }
}