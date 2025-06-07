vale([H|L]) :-
    secv_descrescatoare(L, H, Rest),!,
    Rest = [I|R],
    secv_crescatoare(R, I, Z),!,
    Z = [].


secv_descrescatoare([], _, []) :-
    fail.

secv_descrescatoare([H|L], Prev, R) :-
    H < Prev,
    secv_descrescatoare(L, H, R).

secv_descrescatoare([H|L], Prev, [H|L]) :-
    H >= Prev.


secv_crescatoare([], _, []).

secv_crescatoare([H|L], Prev, R) :-
    H > Prev,
    secv_crescatoare(L, H, R).

secv_crescatoare([H|L], Prev, [H|L]) :-
    H =< Prev.