/*a) Se da o lista de numere intregi.
Se cere sa se scrie de 2 ori in lista
fiecare numar prim.*/
det_prim(N, N).

det_prim(A, N) :-
    N mod A =:= 0,
    fail.

det_prim(A, N) :-
    A * A =:= N,
    fail.

det_prim(A, N) :-
    A < N,
    N mod A =\= 0,
    A1 is A + 1,
    det_prim(A1, N).

% prim(N: int) -determina daca N este prim
% prim(i)
prim(N) :-
    N > 1,
    det_prim(2, N).

% insera_prime(L: List, R: List)
% insera_prime(i, i/o)
insera_prime([], []).

insera_prime([H|T], [H|Rez]) :-
    \+ prim(H),
    insera_prime(T, Rez).

insera_prime([H|T], [H,H|Rez]) :-
    prim(H),
    insera_prime(T, Rez).
