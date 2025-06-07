% Generate candidate numbers between A and B
candidat_aux(E, E, _, _).
candidat_aux(E, I, A, B):- I < B, I1 is I + 1, candidat_aux(E, I1, A, B).
candidat_aux(E, I, A, B):- I >= B, candidat_aux(E, A, A, B).

candidat(E, A, B):- candidat_aux(E, A, A, B).

% Check if an element belongs to a list
apartine(E, [E|_]):- !.
apartine(E, [_|L]):- apartine(E, L).

% Recursive generation of subsets with even sums
submultimi_aux(_, _, Sum, Col, Col):- Sum mod 2 =:= 0, Sum > 0. % Corrected condition
submultimi_aux(A, B, Sum, Col, Rez):- 
    candidat(E, A, B), 
    \+ apartine(E, Col), 
    Sum1 is Sum + E,
    submultimi_aux(A, B, Sum1, [E|Col], Rez).

% Generate all subsets
submultimi(A, B, Rez):- 
    candidat(E, A, B),
    submultimi_aux(A, B, E, [E], Rez).

% Generate all subsets with even sums
submultimi_suma_para(A, B, Rez):- findall(X, submultimi(A, B, X), Rez).
