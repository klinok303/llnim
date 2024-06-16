use llnim_rs::raylib_ref::RaylibRef;
use llnim_rs::animation::*;
use std::mem::{size_of, transmute};
use std::os::raw::{c_char, c_int, c_void};
use raylib::ffi::{sinf, TraceLog, TraceLogLevel};
use std::ptr;
use llnim_rs::env::Env;
use raylib::prelude::Color;

#[repr(C)]
struct Plug {
    size: usize,
    rref: RaylibRef,
    anim: Animation,
}

static mut PLUG: Option<&'static mut Plug> = None;

#[no_mangle]
unsafe extern fn plug_init(rref: RaylibRef) {
    PLUG = Some(Box::leak(Box::new(Plug { size: size_of::<Plug>(), rref, anim: Animation {
        i: 0, dur: 0.0, is_loop: true} })));

    TraceLog(TraceLogLevel::LOG_INFO as c_int, "-------------------".as_ptr() as *const
    c_char);

    TraceLog(TraceLogLevel::LOG_INFO as c_int, "Plugin Init success".as_ptr() as *const
    c_char);

    TraceLog(TraceLogLevel::LOG_INFO as c_int, "-------------------".as_ptr() as *const
    c_char);
}

#[no_mangle]
unsafe extern fn plug_pre_reload() -> *mut c_void {
    PLUG.take().map_or_else(ptr::null_mut, |p| p as *mut Plug) as *mut c_void
}

#[no_mangle]
unsafe extern fn plug_post_reload(state: *mut c_void) {
    PLUG = Some(transmute(state));

    if let Some(plug) = &mut PLUG {
        if plug.size < size_of::<Plug>() {
            TraceLog(TraceLogLevel::LOG_INFO as c_int,
                     format!("Migrating plugin state schema {} -> {} bytes", plug.size,
                             size_of::<Plug>()).as_ptr() as *const c_char);
            plug.size = size_of::<Plug>();
            PLUG = Some(*plug);
        }
    }
}

#[no_mangle]
unsafe extern fn plug_update(env: Env) {
    let keys: [Key; 2] = [
        Key { from: 0.0, to: 1.0, dur: 1.0 },
        Key { from: 1.0, to: 1.0, dur: 1.0 },
    ];

    if let Some(plug) = PLUG.take() {
        (plug.rref.clear_background)(Color::BROWN.into());

        plug.anim.update(&keys, env.dt);

        let v = plug.anim.val(&keys);

        let rect = 100;

        (plug.rref.draw_rectangle)((env.screen_width - rect) * ((sinf(env.time as f32) + 1.0)
            * 0.5) as i32, rect, rect, rect, Color::DARKBLUE.into()W);
    }
}