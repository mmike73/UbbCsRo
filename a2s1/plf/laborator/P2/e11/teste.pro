test_p2a() :-
    insera_prime([1,2,3,4,5,6],[1,2,2,3,3,4,5,5,6]),
    insera_prime([1,2,2,3,4,5,6],[1,2,2,2,2,3,3,4,5,5,6]),
    insera_prime([1,2,3,3,4,5,6],[1,2,2,3,3,3,3,4,5,5,6]),
    insera_prime([1,2,3,4,5,6],[1,2,2,3,3,4,5,5,6]),
    insera_prime([1,2,3,4,5,6],[1,2,2,3,3,4,5,5,6]),
    insera_prime([],[]),
    insera_prime([0],[0]),
    insera_prime([2,0],[2,2,0]),
    insera_prime([-2,0],[-2,0]).

test_p2b() :-
    insera_prime_subliste([],[]),
    insera_prime_subliste([[2]],[[2,2]]),
    insera_prime_subliste([[2,3]],[[2,2,3,3]]),
    insera_prime_subliste([1,2,[2,2]],[1,2,[2,2,2,2]]),
    insera_prime_subliste([2,[2],[4],4],[2,[2,2],[4],4]),
    insera_prime_subliste([[],[],[]],[[],[],[]]),
    insera_prime_subliste([1,2,3,4,5],[1,2,3,4,5]).

run_tests() :-
    test_p2a(),
    test_p2b(),
    write("Teste realizate cu succes!!!").
