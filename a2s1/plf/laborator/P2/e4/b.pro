interclasare2([], []).

interclasare2([H|L], Rez) :-
    \+ is_list(H),
    interclasare2(L, Rez).

interclasare2([H|L], Rez) :-
    is_list(H),
    interclasare2(L, Int),
    interclasare(H, Int, Rez).
