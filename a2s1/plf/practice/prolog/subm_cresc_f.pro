% candidat(E: element, L: list)
% (o, i) - nondeterministic
candidat(E, [E|_]).
candidat(E, [_|T]) :-
    candidat(E, T).

% subm(L: lista, R: lista)
% (i, o) - nondeterministic
subm(L, R) :-
    subm_accum(L, [],R).

% subm_accum(L: list, R: list, Acc: list)
% (i, o, i) - accumulates results in Acc, no findall used
subm_accum([], Acc, Acc).  % Base case: no more elements to process, return the accumulated result.
subm_accum(L, R, Acc) :-
    candidat(E, L),
    subm_aux(L, Sublist, E, [E], []),  % Generate sublist and start accumulation
    subm_accum(L, R, [Sublist|Acc]).

% subm_aux(L: lista, Sublist: list, Last: element, Current: list, Acc: list)
% (i, o, i, i, i) - generates strictly increasing sublists
subm_aux(_, Sublist, _, Sublist, Acc) :-
    len(Sublist, Len),
    Len >= 2,  % The sublist must have at least 2 elements
    reverse(Sublist, Acc).  % Reverse to maintain order

subm_aux(L, Sublist, Last, [H|T], Acc) :-
    candidat(E, L),
    E > Last,  % Ensure the elements are strictly increasing
    subm_aux(L, Sublist, E, [E|[H|T]], Acc).  % Recurse and build sublist

% len/2 - calculate the length of the list
len([], 0).
len([_|L], Len) :-
    len(L, Len1),
    Len is Len1 + 1.
