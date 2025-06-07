reuniune([], Lista2, Lista2).

reuniune([H|Lista1], Lista2, Rez) :-
    member(H, Lista2),
    reuniune(Lista1, Lista2, Rez).

reuniune([H,Lista1], Lista2, [H|Rez]) :-
    \+ member(H, Lista2),
    reuniune(Lista1, Lista2, Rez).
