pub struct Color {
    pub r: i8,
    pub g: i8,
    pub b: i8,
    pub a: i8,
}

pub struct Vector2 {
    pub x: f32,
    pub y: f32,
}

pub struct Rectangle {
    pub x: f32,
    pub y: f32,
    pub width: f32,
    pub height: f32,
}

pub struct Texture {
    pub id: u32,
    pub width: i32,
    pub height: i32,
    pub mipmaps: i32,
    pub format: i32,
}

pub struct RenderTexture {
    pub id: u32,
    pub texture: Texture,
    pub depth: Texture,
}

pub type Texture2D = Texture;
pub type RenderTexture2D = RenderTexture;