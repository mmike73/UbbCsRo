len_lista([], 0).
len_lista([_|T], R) :-
    len_lista(T, R1),
    R is R1+1.

elimina([], _, []).
elimina(T, 0, T) :- !.
elimina([H|T], N, R) :-
    N > 0,
    is_list(H),
    len_lista(H, L),
    0 is L mod 2,!,
    N1 is N - 1,
    elimina(T, N1, R).

elimina([H|T], N, [H|R]) :-
    elimina(T, N, R).
