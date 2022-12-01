read_input_line(Line) :-
    read_string(user_input, "\n", "\r", Sep, Line),
    Sep \= -1. 

solve(Best, Current, Result):-
    read_input_line(Line),
    !,
    process_line(Line, Current, NewCurrent),
    NewBest is max(Best, NewCurrent),
    solve(NewBest, NewCurrent, Result).

solve(Best, _, Best).

process_line("", _, 0).
process_line(Line, Current, NewCurrent):-
    number_string(Num, Line),
    NewCurrent is Current + Num.

main():-
    solve(0, 0, Result),
    write(Result),
    write("\n"),
    halt.

:- main.
% If errors in main
:- halt.