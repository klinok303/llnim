use llnim_rs::raylib_ref::RaylibRef;
use std::mem::{size_of, transmute};
use std::os::raw::{c_char, c_int, c_void};
use raylib::ffi::{TraceLog, TraceLogLevel};
use std::ptr;
use llnim_rs::env::Env;
use raylib::prelude::Color;

#[repr(C)]
struct Plug {
    size: usize,
    rref: RaylibRef,
}

static mut PLUG: Option<&'static mut Plug> = None;

#[no_mangle]
unsafe extern fn plug_init(rref: RaylibRef) {
    PLUG = Some(Box::leak(Box::new(Plug { size: size_of::<Plug>(), rref })));

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
unsafe extern fn plug_update(_: Env) {
    if let Some(plug) = &PLUG { (plug.rref.clear_background)(Color::LIGHTGRAY.into()); }
}