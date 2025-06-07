candidat(E, E, _).
candidat(E, K, N):-
    K < N,
    K1 is K + 1,
    candidat(E, K1, N).

combinari(N, K, Rez):-
    findall(X, combinari_helper(N, K, 1, [], X), Rez).

combinari_helper(_, 0, _, Col, Col):- !.
combinari_helper(N, K, Start, Col, R):-
    K > 0,
    candidat(E, Start, N),
    K1 is K - 1,
    E1 is E + 1,
    combinari_helper(N, K1, E1, [E|Col], R).