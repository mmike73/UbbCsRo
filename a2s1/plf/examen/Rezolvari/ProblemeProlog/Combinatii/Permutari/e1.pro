candidat(E, N):-
    candidat_aux(E, N, N). 

candidat_aux(E, E, _).
candidat_aux(E, I, N):-
    I < 2 * N - 1,
    I1 is I + 1,
    candidat_aux(E, I1, N).

permutari(N, Rez):-
    findall(X, permutari_aux(N, 0, [], X), Rez).

permutari_aux(N, N, Col, Col).

permutari_aux(N, K, [], Rez) :-
    K < N,
    candidat(E, N),
    K1 is K + 1,
    permutari_aux(N, K1, [E], Rez).

permutari_aux(N, K, [H|Col], Rez) :-
    K < N,
    candidat(E, N),
    \+ member(E, [H|Col]),
    2 >= abs(E - H),
    K1 is K + 1,
    permutari_aux(N, K1, [E,H|Col], Rez).
