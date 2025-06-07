candidat([E|_], E).
candidat([_|T], E) :- 
   candidat(T, E).

apartine(E, [E|_]).
apartine(E, [_|L]) :-
    apartine(E, L).

sum_helper(_, R, K, S, R) :- 
    K > 0, 
    0 is S mod 3.
sum_helper(L, R, K, S, [H|Col]) :-
    candidat(L, E),
    \+ apartine(E, Col),
    H < E,
    K1 is K + 1,
    S1 is S + E,
    sum_helper(L, R, K1, S1, [E|[H|Col]]).

subm_sum_div_3(L, R) :-
    candidat(L, E),
    sum_helper(L, R, 1, E, [E]).

