prim(2):- !.
prim(N):- N < 2, !, fail.
prim(N):- 0 is N mod 2, !, fail.
prim(N):- 
    prim_aux(N, 3).

prim_aux(N, D) :-
    N < D * D, !.
prim_aux(N, D):-
    0 is N mod D, !,
    fail.
prim_aux(N, D):-
    D1 is D + 2,
    prim_aux(N, D1).


%elimina_n_prime(L, N, R)
elimina_n_prime(L, 0, L) :- !.
elimina_n_prime([H|T], N, R) :-
    N > 0,
    prim(H), !,
    N1 is N - 1,
    elimina_n_prime(T, N1, R).
elimina_n_prime([H|T], N, [H|R]) :-
    elimina_n_prime(T, N, R).
