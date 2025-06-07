/*b) Se da o lista eterogena, formata din numere intregi si liste de numere
intregi. Se cere ca in fiecare sublista sa se scrie de 2 ori fiecare numar
prim. De ex:
[1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5] =>
[1, [2, 2, 3, 3], 4, 5, [1, 4, 6], 3, [1, 3, 3, 7, 7, 9, 10], 5]*/

% is_list_mine(L: List)
% is_list_mine(i) determina daca L este o lista
is_list_mine([]).

is_list_mine([_|T]) :-
    is_list_mine(T).

is_list_faster([_|_]).


% insera_prime_subliste(L: List, R: List)
% insera_prime_subliste(i, i/o)
insera_prime_subliste([], []).

insera_prime_subliste([H|T], [H|Rez]) :-
    \+ is_list_faster(H),
    insera_prime_subliste(T, Rez).

insera_prime_subliste([H|T], [Modificat|Rez]) :-
    is_list_faster(H),
    insera_prime(H, Modificat),
    insera_prime_subliste(T, Rez).
