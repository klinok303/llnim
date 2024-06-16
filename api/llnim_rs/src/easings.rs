use std::f32::consts::PI;

pub fn ease_in_sine(x: f32) -> f32 { 1.0 - (x * PI / 2.0).cos() }
pub fn ease_out_sine(x: f32) -> f32 { (x * PI / 2.0).sin() }
pub fn ease_in_out_sine(x: f32) -> f32 { -((x * PI).cos() - 1.0) / 2.0 }
pub fn ease_in_quad(x: f32) -> f32 { x * x }
pub fn ease_out_quad(x: f32) -> f32 { 1.0 - (1.0 - x).powi(2) }
pub fn ease_in_out_quad(x: f32) -> f32 {
    if x < 0.5 { 2.0 * x * x }
    else { 1.0 - (-2.0 * x + 2.0).powi(2) / 2.0 }