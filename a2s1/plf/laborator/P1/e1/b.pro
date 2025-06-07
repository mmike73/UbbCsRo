insert1([], []).

insert1([H|L], [H,1|R]) :-
    0 is H mod 2, % =:=
    insert1(L, R).

insert1([H|L], [H|R]) :-
    \+ 0 is H mod 2,
    insert1(L, R).
