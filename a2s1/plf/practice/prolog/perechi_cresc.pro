% pereche(E: element, L: lista, R: lista)
% (i, i, o) - nedeterminist
% produce perechi in ordine crescatoare intre elementul dat si
% elementele listei argument

pereche(A, [B|_], [A,B]) :-
	A < B.

pereche(A, [_|T], P) :-
	pereche(A, T, P).

% perechi(L: lista, Col: lista, R: lista)
% (i, i, o) - determinist

perechi([], Col, Col).

perechi([H|T], Col, R) :-
	colecteaza_perechi(H, T, Col, NCol),
	perechi(T, NCol, R).

% colecteaza_perechi(E: element, L: lista, Col: lista, NCol: lista)
% (i, i, i, o) - determinist
colecteaza_perechi(_, [], Col, Col).

colecteaza_perechi(A, [B|T], Col, NCol) :-
	A < B,
	adauga_pereche([A, B], Col, TmpCol),
	colecteaza_perechi(A, T, TmpCol, NCol).

colecteaza_perechi(A, [_|T], Col, NCol) :-
	colecteaza_perechi(A, T, Col, NCol).


% adauga_pereche(P: list, L: list, R: list)
% (i, i, o) - determinist
adauga_pereche(P, [], [P]).

adauga_pereche(P, [H|T], [H|R]) :-
	adauga_pereche(P, T, R).


% toate_perechile(L: lista, R: lista)
% (i, o) - determinist
toate_perechile(L, R) :-
	perechi(L, [], R).
