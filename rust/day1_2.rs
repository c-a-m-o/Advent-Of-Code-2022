use std::io::{BufRead, BufReader};

fn lines() -> impl Iterator<Item = String> {
    BufReader::new(std::io::stdin()).lines().map(Result::unwrap)
}

fn main() {
    let mut max_vals = [0; 3];
    lines().fold(0, |sum, line| match line.parse::<i32>() {
        Ok(x) => sum + x,
        Err(_) => {
            if sum > max_vals[0] {
                max_vals[0] = sum;
                max_vals.sort();
            }
            0
        }
    });
    let res: i32 = max_vals.iter().sum();
    println!("{res}");
}
