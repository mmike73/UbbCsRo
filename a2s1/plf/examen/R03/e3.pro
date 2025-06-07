candidat1(_, N, N).
candidat1(Bound, N, E):-
    N1 is (N + 1) mod Bound + Bound,
    candidat1(Bound, N1, E).

candidat(N, N).
candidat(N, I) :-
	N > 1,
	N1 is N - 1,
	candidat(N1, I).

apare(E, [E|_]):- !.
apare(E, [_|T]):-
    apare(E, T).

permutari(N, L) :-
    candidat(N,I),
    E is I + N,
    permutari_helper(N, L, 1, [E]).

permutari_helper(N, Col, N, Col):- !.
permutari_helper(N, L, Lg, [H|T]):-
    candidat(N, I),
    E is I + N,
    abs(H-E) =< 2,
    \+ apare(E, [H|T]),
    Lg1 is Lg + 1,
    permutari_helper(N, L, Lg1, [E|[H|T]]).