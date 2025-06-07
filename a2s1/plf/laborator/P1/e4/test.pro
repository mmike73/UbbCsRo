test_4a() :-
    substituie(3,[1,2,3,4,5,6],[a,b,c,d],[1, 2, 3, [a, b, c, d], 5, 6]),

    substituie(3,[1,2,3,4],[a,b,c,d],[1, 2, 3,[ a, b, c, d]]),
    substituie(0,[1,2,3],[a,b,c,d],[[a, b, c, d], 2, 3]),
    substituie(5,[1,2,3,4,5,6],[a,b,c,d],[1, 2, 3, 4, 5, [a, b, c, d]]),
    substituie(0,[0],[a,b,c,d],[[ a, b, c, d]]),
    substituie(0,[0],[],[[]]),
    \+ substituie(0, [], [], []),
    write("test_4a realizat cu succes!"), nl.


test_4b() :-
    sterge_poz(0,[1,2,3,4,5],[2,3,4,5]),
    sterge_poz(1,[1,2,3,4,5],[1,3,4,5]),
    sterge_poz(2,[1,2,3,4,5],[1,2,4,5]),
    sterge_poz(3,[1,2,3,4,5],[1,2,3,5]),
    sterge_poz(4,[1,2,3,4,5],[1,2,3,4]),
    sterge_poz(0,[0],[]),
    \+ sterge_poz(2,[],[]),
    \+ sterge_poz(7,[1,2,3,4,5],[1,2,3,4,5,6]),
    write("test_4b realizat cu succes!").

teste() :-

    test_4a(),
    test_4b().
