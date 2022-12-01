read_input_line(Line) :-
    read_string(user_input, "\n", "\r", Sep, Line),
    Sep \= -1. 

solve(Sums, Result):-
    read_input_line(Line),
    !,
    process_line(Line, Sums, NewSums),
    solve(NewSums, Result).

solve(Sums, Result):-
    sort(Sums, Sorted),
    reverse(Sorted, [X,Y,Z|_]),
    Result is X + Y + Z.

process_line("", Sums, [0|Sums]).
process_line(Line, [H|T], [NewH|T]):-
    number_string(Num, Line),
    NewH is H + Num.

main():-
    solve([0], Result),
    write(Result),
    write("\n"),
    halt.

:- main.
% If errors in main
:- halt.