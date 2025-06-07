% 2 * n - 1

insert([], _, _, _, []).
insert([H|T], E, INDI, INDI, [H|[E|Rez]]) :-
    !,
    INDI1 is 2 * INDI - 1,
    IND1 is INDI + 1,
    insert(T, E, IND1, INDI1, Rez).
insert([H|T], E, IND, INDI, [H|Rez]) :-
    IND1 is IND + 1,
    insert(T, E, IND1, INDI, Rez).


insereaza_dupa_35917(L, E, Rez) :-
    insert(L, E, 1, 3, Rez),
    write(Rez).