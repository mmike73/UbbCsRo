/* 8. Un jucator la PRONOSPORT vrea sa aleaga pronosticuri pentru 4 meciuri.
Pronosticurile pot fi 1,X,2. Sa se genereze toate variantele posibile stiind ca:
- ultimul pronostic nu poate fi 2
- sa nu fie mai mult de doua pronosticuri X.

m1 m2 m3 m4
1  1  1  1
X  X  X  X  maxim 2
2  2  2
*/

% candidat(E: element, L: lista)
% (o, i) - nedeterminist
candidat(E, [E|_]).

candidat(E, [_|T]) :-
    candidat(E, T).

% este_X(E: element, NX: intreg)
% (i, o) - determinist
este_X(E, NX) :-
    E = 'X', 
    NX is 1.

este_X(E, NX) :-
    \+ E = 'X', 
    NX is 0.


% adauga(L: lista, E: element, R: lista)
% (i, i, o) - determinist
adauga([], E, [E]) :- !.

adauga([H|T], E, [H|R]) :-
    adauga(T, E, R).


% delete_2(L: lista, R: lista)
% (i, o) - determinist
delete_2([], []).

delete_2([H|T], [H|R]) :-
    \+ H = '2',
    delete_2(T, R).

delete_2([H|T], R) :-
    H = '2',
    delete_2(T, R).


% perm(L: lista, K: intreg, R: lista)
% (i, i, o) - nedeterminist
perm(L, K, R) :-
    candidat(E, L),
    este_X(E, NX),
    perm_helper(L, K, R, 1, NX, [E]).


% perm_helper(L: lista, K: intreg, R: lista, I: intreg, NX: intreg, Col: lista)
% (i, i, i, i, o) - nedeterminist
perm_helper(_, K, Col, K, _, Col).

perm_helper(L, K, R, I, NX, Col) :-
    candidat(E, L),
    I1 is I + 1,
    I1 < K,
    este_X(E, AX),
    NX1 is AX + NX,
    NX1 =< 2,
    adauga(Col, E, Col1),
    perm_helper(L, K, R, I1, NX1, Col1).

perm_helper(L, K, R, I, NX, Col) :-
    delete_2(L, Ot),
    candidat(E, Ot),
    candidat(E, L),
    I1 is I + 1,
    I1 = K,
%    \+ E = '2',
    este_X(E, AX),
    NX1 is AX + NX,
    NX1 =< 2,
    adauga(Col, E, Col1),
    perm_helper(L, K, R, I1, NX1, Col1).


determina_pronosticuri(NrMeciuri, ToatePron) :-
    findall(R, perm(['1','X','2'], NrMeciuri, R), ToatePron).

