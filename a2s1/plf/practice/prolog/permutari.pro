% apare(I: element, L: lista)
% (i, i) - determinist
apare(_, []) :- fail.

apare(I, [I|_]) :- !.

apare(I, [_|T]) :-
	apare(I, T).

% candidat(N: intreg, I: intreg)
% (i, o) - nedeterminist
candidat(N, N).

candidat(N, I) :-
	N > 1,
	N1 is N - 1,
	candidat(N1, I).
	
% (N: integer, V: integer, L: list)
% (i, i, o) - nedeterminist
permutari(N, V, L) :-
	candidat(N, I),
	permutari_aux(N, V, L, 1, [I]).
	
% permutari_aux(N: intreg, V: intreg, L: lista, Lg: intreg, Col: lista)
% (i, i, o, i, i) - nedeterminist
permutari_aux(N, _, Col, N, Col) :- !.

permutari_aux(N, V, L, Lg, [H|T]) :-
	candidat(N, I),
	Cmp is abs(H - I),
    Cmp >= V,
	\+ apare(I, [H|T]),
	Lg1 is Lg + 1,
	permutari_aux(N, V, L, Lg1, [I|[H|T]]).