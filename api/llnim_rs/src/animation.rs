use raylib::math::lerp;

/// Keyframe structure
#[derive(Debug)]
pub struct Key {
    pub from: f32,
    pub to: f32,
    pub dur: f32,
}

/// Animation struct
#[derive(Debug)]
pub struct Animation {
    pub i: usize,
    pub dur: f32,
    pub is_loop: bool,
}

impl Animation {
    /// Animation update function
    pub fn update(&mut self, keys: &[Key], dt: f32) {
        if self.i >= keys.len() {
            if self.is_loop {
                self.i = 0;
                self.dur = 0.0;
            }
            else { return; }
        }

        self.dur += dt;

        while self.i < keys.len() && self.dur >= keys[self.i].dur {
            self.dur -= keys[self.i].dur;
            self.i += 1;
        }
    }

    /// Function for get a value of keyframe lerp
    pub fn val(&self, keys: &[Key]) -> f32 {
        assert!(!keys.is_empty());

        if self.i >= keys.len() { return keys[keys.len() - 1].to; }
        let kf = &keys[self.i];

        lerp(kf.from, kf.to, self.dur / kf.dur)
    }
}