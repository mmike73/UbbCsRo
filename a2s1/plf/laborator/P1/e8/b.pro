/*Sa se scrie un predicat care elimina primele 3 aparitii ale unui element
  intr-o lista. Daca elementul apare mai putin de 3 ori, se va elimina de
  cate ori apare.*/

my_isin(_, []) :-
    fail.

my_isin(E, [E|_]).

my_isin(E, [_|D]) :-
    my_isin(E, D).


elim_3(_, _, [], []).

elim_3(_, 0, L, L).

elim_3(E, K, [H|L], R) :-
    K > 0,
    H is E,
    K1 is K - 1,
    elim_3(E, K1, L, R).

elim_3(E, K, [H|L], [H|R]) :-
    elim_3(E, K, L, R).


elimina_aux([], _, []).

elimina_aux([H|L], D, R) :-
    \+ my_isin(H, D),
    elim_3(H, 3, [H|L], L1),
    elimina_aux(L1, [H|D], R).

elimina_aux([H|L], D, [H|R]) :-
    my_isin(H, D),
    elimina_aux(L, D, R).


elimina(L, R) :-
    elimina_aux(L, [], R).

