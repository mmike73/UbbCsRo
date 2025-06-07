candidat(E, [E|_]).
candidat(E, [_|T]):-
    candidat(E, T).

apartine(E, [E|_]):- !.
apartine(E, [_|T]):- apartine(E, T).

%aranj_helper(L, S, K, Scrt, Ncrt, Rez, Col)
aranj_helper(_, Scrt, Ncrt, Scrt, Ncrt, Rez, Rez) :- !.
aranj_helper(L, S, K, Scrt, Ncrt, Rez, Col) :-
    candidat(E, L),
    \+ apartine(E, Col),
    S1 is Scrt + E,
    S1 =< S,
    K1 is Ncrt + 1,
    K1 =< K,
    aranj_helper(L, S, K, S1, K1, Rez, [E|Col]).


aranj_sum_k(L, S, K, Rez):-
    aranj_helper(L, S, K, 0, 0, Rez, []).