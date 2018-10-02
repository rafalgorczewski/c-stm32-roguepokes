extern crate image;

use std::env;
use std::fs::File;
use std::io::prelude::*;

use image::GenericImage;
use image::Pixel;

fn main() {
    let args: Vec<String> = env::args().collect();
    let path = &args[1];
    let output_file_name = &args[2];

    let mut file = File::create(output_file_name).unwrap();
    let img = image::open(path).unwrap().rotate270().flipv();

    let (width, height) = (img.width(), img.height());

    file.write_all(
        (format!("const uint16_t NAME[{}] = ", width * height) + "{")
            .into_bytes()
            .as_slice(),
    ).unwrap();

    for x in 0..width {
        for y in 0..height {
            let rgb = img.get_pixel(x, y).to_rgba();
            let (r, g, mut b, alpha) = (rgb[0] as u32, rgb[1] as u32, rgb[2] as u32, rgb[3] as u32);
            println!("{}, {}, {}, {}", r, g, b, alpha);
            if r == 0 && g == 0 && b == 0 {
                b = 1 << 3;
            }
            let colour: u32 = if alpha < 50 {
                0
            } else {
                (b >> 3) | ((g >> 2) << 5) | ((r >> 3) << 11)
            };
            let brackets = match y {
                _y if x == width - 1 && _y == height - 1 => format!("{}", colour),
                _ => format!("{},", colour),
            };

            file.write_all(brackets.into_bytes().as_slice()).unwrap();
        }
    }
    file.write_all(b"};").unwrap();
}
