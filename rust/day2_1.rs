use std::io::{BufRead, BufReader};

fn lines() -> impl Iterator<Item = String> {
    BufReader::new(std::io::stdin()).lines().map(Result::unwrap)
}

/// An action that can be done in the Rock Paper Scissors game.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Move {
    Rock,
    Paper,
    Scissors,
}

impl Move {
    /// Creates a move from its string representation.
    fn from_str(input: &str) -> Self {
        match input {
            "A" | "X" => Self::Rock,
            "B" | "Y" => Self::Paper,
            "C" | "Z" => Self::Scissors,
            _ => panic!("Parsing error"),
        }
    }
    /// The number of points awarded by playing this move.
    fn points(&self) -> usize {
        match self {
            Self::Rock => 1,
            Self::Paper => 2,
            Self::Scissors => 3,
        }
    }
    /// The result of a match where the opponent plays the move `other`.
    fn play(&self, other: Move) -> MatchResult {
        use Move::*;
        match (self, other) {
            (Rock, Scissors) | (Paper, Rock) | (Scissors, Paper) => MatchResult::Win,
            (Rock, Rock) | (Paper, Paper) | (Scissors, Scissors) => MatchResult::Tie,
            (Rock, Paper) | (Paper, Scissors) | (Scissors, Rock) => MatchResult::Loss,
        }
    }
}

/// The result of a Rock Paper Scissors match.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum MatchResult {
    Win,
    Loss,
    Tie,
}

impl MatchResult {
    /// The number of points awarded for this outcome.
    fn points(&self) -> usize {
        match self {
            Self::Loss => 0,
            Self::Tie => 3,
            Self::Win => 6,
        }
    }
}

fn main() {
    let res: usize = lines()
        .map(|line| {
            let (opp_move, mov) = line.split_once(' ').expect("Parsing error");
            let opp_move = Move::from_str(opp_move);
            let mov = Move::from_str(mov);

            mov.points() + mov.play(opp_move).points()
        })
        .sum();
    println!("{res}");
}
