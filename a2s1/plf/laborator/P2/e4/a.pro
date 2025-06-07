interclasare([], P, P).

interclasare(L, [], L).

interclasare([H1|L], [H2|P], [H1|Rez]) :-
    H1 < H2,
    interclasare(L, [H2|P], Rez).

interclasare([H1|L], [H2|P], [H2|Rez]) :-
    H1 > H2,
    interclasare([H1|L], P, Rez).

interclasare([H1|L], [H2|P], [H1|Rez]) :-
    H1 = H2,
    interclasare(L, P, Rez).
