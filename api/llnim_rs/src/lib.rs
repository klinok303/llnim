//! # llnim-rs
//!
//! `llnim-rs` is a safe Rust binding to llnim plugin api.
//!
//! `llnim` is dl-based animation engine.

pub mod raylib_ref;
pub mod easings;
pub mod animation;
pub mod env;

use std::os::raw::{c_int, c_char};
use raylib::ffi::{TraceLogLevel, TraceLog};

pub fn log_trace(level: TraceLogLevel, message: &str) {
    unsafe { TraceLog(level as c_int, message.as_ptr() as *const c_char); }
}
