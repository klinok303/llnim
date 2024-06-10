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
    i: usize,
    dur: f32,
    is_loop: bool,
}

impl Animation {
    /// Animation update function
    pub fn update(&mut self, keys: Vec<Key>, dt: f32) {
        if self.i >= keys.len() {
            if self.is_loop {
                self.i = 0;
                self.dur = 0.0;
            }
            else { None }
        }

        self.dur += dt;

        while self.i < keys.len() && self.dur >= keys[self.i].dur {
            self.dur -= keys[self.i].dur;
            self.i += 1;
        }
    }

    /// Function for get a value of keyframe lerp
    pub fn val(&self, keys: Vec<Key>) -> f32 {
        assert!(keys.len() > 0);

        if self.i >= keys.len() {
            match keys.last() {
                Some(last_element) => { last_element.to },
                None => { println!("Keys vector is empty"); }
            }
        }

        let kf = &keys[self.i];
        lerp(kf.from, kf.to, self.dur/kf.dur)
    }
}