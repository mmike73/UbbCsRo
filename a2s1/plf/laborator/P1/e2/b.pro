pow2(1) :- !.
pow2(N) :-
    N > 0,
    0 is N mod 2,
    N1 is N div 2,
    pow2(N1).


inject_p2([], _, _, []).

inject_p2([H|L], Cnt, V, [H, V|Rez]) :-
    pow2(Cnt),
    Cnt1 is Cnt + 1,
    inject_p2(L, Cnt1, V, Rez).

inject_p2([H|L], Cnt, V, [H|Rez]) :-
    \+ pow2(Cnt),
    Cnt1 is Cnt + 1,
    inject_p2(L, Cnt1, V, Rez).

operatie2b(L, V, R) :-
    inject_p2(L, 1, V, R).