% candidat(E: element, L: lista)
% (o, i) - nedeterminist
candidat(E, [E|_]) :-
    1 =:= E mod 2.

candidat(E, [_|T]) :-
    candidat(E, T).


submspei(L, R) :-
    candidat(E, L),
    submspe_aux(L, R, E, E, [E]).

submspe_aux(_, Col, S, _, Col) :-
    0 =:= S mod 2.

submspe_aux(L, R, S, Last, [H|T]) :-
    candidat(E, L),
    \+ Last = E,
    E =< Last,
    S1 is S + E,
    submspe_aux(L, R, S1, E, [E,H|T]).
