% candidat(E: element, L: lista)
% (o, i) - nedeterminist
candidat(E, [E|_]).

candidat(E, [_|T]) :-
	candidat(E, T).

% comb_suma(L: lista, K: intreg, S: intreg, C: lista)
% (i, i, i, o) - nedeterminist
comb_suma(L, K, S, C) :-
	candidat(E, L),
	E =< S,
	comb_aux(L, K, S, C, 1, E, [E]).

% comb_aux(L: lista, K: intreg, S: intreg, C: lista, Lg: intrg, Sc: intreg, Col: lista)
% (i, i, i, o, i, ,i ,i) - nedeterminist
comb_aux(_, K, S, C, K, S, C) :-
	!.

comb_aux(L, K, S, C, Lg, Sc, [H|T]) :-
	Lg < K,
	candidat(E, L),
	E < H,
	Sc1 is Sc + E,
	Sc1 =< S,
	Lg1 is Lg + 1,
	comb_aux(L, K, S, C, Lg1, Sc1, [E|[H|T]]).
