%recursiva
reuniune2([],L2,L2). % basecase - aici ajunge prima lista vida ([] - lista vida)
                     % L3, adica al treilea parametru devine L2, addica al doilea 
                     % parametru
reuniune2([H|T], L3, L2) :-
    member(H,L2),
    reuniune2(T,L3,L2).

reuniune2([H|T],[H|L3], L2) :-
    \+ member(H,L2),
    reuniune2(T,L3,L2).