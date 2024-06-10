use std::f32::consts::PI;

pub fn ease_in_sine(x: f32) -> f32 { 1 - (x * PI / 2).cos() }
pub fn ease_out_sine(x: f32) -> f32 { (x * PI / 2).sin() }
pub fn ease_in_out_sine(x: f32) -> f32 { -((x * PI).cos() - 1) / 2 }
pub fn ease_in_quad(x: f32) -> f32 { x * x }
pub fn ease_out_quad(x: f32) -> f32 { 1 - (1 - x).powi(2) }
pub fn ease_in_out_quad(x: f32) -> f32 {
    if x < 0.5 { 2 * x * x }
    else { 1 - (-2 * x + 2).powi(2) / 2 }
}