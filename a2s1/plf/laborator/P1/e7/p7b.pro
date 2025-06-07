genereaza_perechi([],[]).
%base case, lista goala

genereaza_perechi([_],[]).
%base case, cand o lista are doar un element, nu se poate genera o pereche

genereaza_perechi([H|L],Rez) :-
    findall((H,X),member(X,L), HeadPairs),
    genereaza_perechi(L, TailPairs),
    append(HeadPairs,TailPairs,Rez).

%findall(Template, Goal, List).
% (H,X) - toate perechile cu primul element H, X - membri al L => fa lista cu perechile
% acelasi lucru pentru lista fara primul element
% concatenez rezultatul => toate perechile


candidat(E, [E|_]).
candidat(E, [_|T]) :-
    candidat(E, T).

perechi(L, K, R) :-
    candidat(E, L),
    perechi_aux(L, K, R, 1, [E]).

perechi_aux(_, K, Col, K, Col).

perechi_aux([H|L], K, R, I, Col) :-
    candidat(E, [H|L]),
    I1 is I + 1,
    perechi_aux(L, K, R, I1, [E|Col]).
    