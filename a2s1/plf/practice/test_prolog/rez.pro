
% cnt_occ(E: element, L: lista, O: intreg)
% (i, i, o) - determinist
cnt_occ(_, [], 0) :-
    !.

cnt_occ(E, [E|L], O) :-
    cnt_occ(E, L, O1),
    !,
    O is O1 + 1.

cnt_occ(E, [_|L], O) :-
    cnt_occ(E, L, O).


% my_member(E: element, L: lista)
% (i, i) - determinist
my_member(_, []) :-
    fail.

my_member(E, [E|_]) :-
    !.

my_member(E, [_|L]) :-
    my_member(E, L).

% genereaza_perechi(L: lista, R: lista de liste)
% (i, o) - determinist
genereaza_perechi(L, R) :-
    gp_helper(L, [], R).

% gp_helper(L: lista, P: lista, R: lista de liste)
% (i, i, o) - determinist
gp_helper([], _, []).

gp_helper([H|L], P, [[H, Cnt]|R]) :-
    \+ my_member(H, P),
    cnt_occ(H, [H|L], Cnt),
    gp_helper(L, [H|P], R).

gp_helper([H|L], P, R) :-
    my_member(H, P),
    gp_helper(L, P, R).




