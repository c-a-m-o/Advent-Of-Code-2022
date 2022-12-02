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
            "A" => Self::Rock,
            "B" => Self::Paper,
            "C" => Self::Scissors,
            _ => panic!("Parsing error"),
        }
    }
    /// Returns the move to play against this move to get the expected result.
    fn move_to_play(&self, expected_result: MatchResult) -> Self {
        use MatchResult::*;
        use Move::*;
        match (self, expected_result) {
            (Rock, Win) | (Paper, Tie) | (Scissors, Loss) => Paper,
            (Paper, Win) | (Scissors, Tie) | (Rock, Loss) => Scissors,
            (Scissors, Win) | (Rock, Tie) | (Paper, Loss) => Rock,
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
}

/// The result of a Rock Paper Scissors match.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum MatchResult {
    Win,
    Loss,
    Tie,
}

impl MatchResult {
    /// Creates a match result from its string representation.
    fn from_str(input: &str) -> Self {
        match input {
            "X" => Self::Loss,
            "Y" => Self::Tie,
            "Z" => Self::Win,
            _ => panic!("Parsing error"),
        }
    }
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
            let (opp_move, result) = line.split_once(' ').expect("Parsing error");
            let opp_move = Move::from_str(opp_move);
            let result = MatchResult::from_str(result);

            opp_move.move_to_play(result).points() + result.points()
        })
        .sum();
    println!("{res}");
}
