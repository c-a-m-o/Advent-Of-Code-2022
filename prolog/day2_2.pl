% Model

% move(+MoveChar, -MoveAtom)
% Converts a move character into the corresponding atom
move("A", rock).
move("B", paper).
move("C", scissors).

% Selects the move based on the instruction character and the
% opponent move.
select_move("X", Choice, OpponentChoice):-
    wins(OpponentChoice, Choice).
select_move("Y", Choice, Choice).
select_move("Z", Choice, OpponentChoice):-
    wins(Choice, OpponentChoice).

% choice_score(+MoveAtom, -Score)
% The score given by a choice
choice_score(rock, 1).
choice_score(paper, 2).
choice_score(scissors, 3).

% wins(Choice, OpponentChoice)
% Holds if Choice wins against OpponentChoice
wins(rock, scissors).
wins(paper, rock).
wins(scissors, paper).

% match_score(Choice, OpponentChoice, Score)
% The number of points made by the result of the match
match_score(Choice, OpponentChoice, 0):-
    wins(OpponentChoice, Choice). % Defeat
match_score(Choice, Choice, 3). % Tie
match_score(Choice, OpponentChoice, 6):-
    wins(Choice, OpponentChoice).

% Total score of the match
score(Choice, OpponentChoice, Score):-
    choice_score(Choice, ChoiceScore),
    match_score(Choice, OpponentChoice, MatchScore),
    Score is ChoiceScore + MatchScore.


% Reads a line of the input. Removes the endline character(s)
% Fails if EOF is reached
read_input_line(Line) :-
    read_string(user_input, "\n", "\r", _, Line). 

% Splits an input line into two characters representing the input
% then convert those characters into the corresponding moves
parse_line(Line, Choice, OppChoice):-
    split_string(Line, " ", " ", [OppChoiceChar, ChoiceChar]),
    move(OppChoiceChar, OppChoice),
    select_move(ChoiceChar, Choice, OppChoice).


solve(Score):-
    solve(0, Score).

solve(CurrentScore, Score):-
    read_input_line(Line),
    parse_line(Line, Choice, OppChoice),
    !,
    score(Choice, OppChoice, MatchScore),
    NewScore is CurrentScore + MatchScore,
    solve(NewScore, Score).

solve(CurrentScore, CurrentScore).

main():-
    solve(Score),
    write(Score),
    write("\n").

% Run the main predicate, then halts
:-main, halt.
:-halt.
