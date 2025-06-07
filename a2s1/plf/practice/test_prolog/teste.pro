test_cnt_occ() :-
    cnt_occ(1,[1,2,1,2,1,3,1], 4).

test_my_member() :-
    my_member(4,[1,2,3,4]),
    \+ my_member(5,[1,2,3,4]).

test_gp() :-
    genereaza_perechi([11,22,11,22,11,33,11], [[11,4],[22,2],[33,1]]),
    genereaza_perechi([1,2,3,4,5], [[1,1],[2,1],[3,1],[4,1],[5,1]]),
    genereaza_perechi([1,1,1,1,1], [[1,5]]),
    genereaza_perechi([1,2,1,3,2,1,5], [[1,3],[2,2],[3,1],[5,1]]),
    genereaza_perechi([1,1,1,1,1,2,2,2,2,2,2,2], [[1,5],[2,7]]),
    genereaza_perechi([], []).


test() :-
    test_cnt_occ(),
    test_my_member(),
    test_gp(),
    write("Teste realizate cu succes").