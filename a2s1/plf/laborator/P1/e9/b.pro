interval(B, B, []).

interval(B, E, [B|R]) :-
    B =< E,
    B1 is B + 1,
    interval(B1, E, R).

    