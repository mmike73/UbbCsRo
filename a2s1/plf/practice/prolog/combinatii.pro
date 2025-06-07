% comb_suma(L: lista, K: intreg, S: intreg, C: lista)
% (i, i, i, o) - nedeterminist
comb_suma([H|_], 1, H, [H]).

comb_suma([_|T], K, S, C) :-
	comb_suma(T, K, S, C).

comb_suma([H|T], K, S, [H|C]) :-
	K > 1,
	S1 is S - H,
	S1 > 0,
	K1 is K - 1,
	comb_suma(T, K1, S1, C).

% toate_comb_suma(L: lista, K: intreg, S: intreg, LC: lista de liste)
% (i, i, i, o) - determinist
toate_comb_suma(L, K, S, LC) :-
	findall(C, comb_suma(L, K, S, C), LC).
