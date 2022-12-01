use std::io::{BufRead, BufReader};

fn lines() -> impl Iterator<Item = String> {
    BufReader::new(std::io::stdin()).lines().map(Result::unwrap)
}

fn main() {
    let mut max = 0;
    lines().fold(0, |sum, line| match line.parse::<i32>() {
        Ok(x) => sum + x,
        Err(_) => {
            max = sum.max(max);
            0
        }
    });
    println!("{max}");
}
