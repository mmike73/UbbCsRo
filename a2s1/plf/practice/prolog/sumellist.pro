candidat([E|_], E).
candidat([_|T], E) :-
	candidat(T, E).
	
solutie(L, N, Rez) :-
	candidat(L, E),
	E =< N,
	sol_aux(L, N, Rez, [E], E).
	
sol_aux(_, N, Rez, Rez, N) :- !.
sol_aux(L, N, Rez, [H|Col], S) :-
	candidat(L, E),
	E < H, %????
	S1 is S + E, 
	S1 =< N,
	sol_aux(L, N, Rez, [E|[H|Col]], S1).
	