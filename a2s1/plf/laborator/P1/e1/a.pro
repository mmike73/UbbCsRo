%Sa se scrie un predicat care intoarce diferenta a doua multimi.

% apartine(E: element, L: lista)
% (i, i) - determinist
apartine(_, []) :-
    fail.

apartine(E, [E|_]).

apartine(E, [_|T]) :-
    apartine(E, T).

% dif_mul(L1: lista, L2: lista, R: lista)
% (i, i, o) - determinist
dif_mul([], _, []).

dif_mul([H|L1], L2, [H|R]) :-
    \+ apartine(H, L2),
    dif_mul(L1, L2, R).

dif_mul([H|L1], L2, R) :-
    apartine(H, L2),
    dif_mul(L1, L2, R).