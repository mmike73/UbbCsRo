inc1(_, 0, 1):- !.
inc1(N, K, R):-
    0 is K mod 2, !,
    K1 is K div 2,
    inc1(N, K1, R1),
    R is R1 * R1.
inc1(N, K, R):-
    K1 is K - 1,
    inc1(N, K1, R1),
    R is R1 * N.


inc2(_, 0, 1):-!.
inc2(N, K, R):-
    K1 is K - 1,
    inc2(N, K1, R1),
    R is R1 * N.