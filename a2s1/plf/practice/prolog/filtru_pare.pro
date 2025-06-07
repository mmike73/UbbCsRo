filtru_pare([], []).

filtru_pare([H|T], [H|R]) :-
	0 is H mod 2,
	filtru_pare(T, R).

filtru_pare([H|T], R) :-
	\+ 0 is H mod 2,
	filtru_pare(T, R).


pare([], []).
	pare([H|T], [H |Rez]) :-
	H mod 2 =:= 0,
	!,
	pare(T,Rez).

pare([_|T], Rez) :-
	pare(T,Rez).
