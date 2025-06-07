% subm(L: lista, Subm: lista)
% (i, o) - nedeterminist
subm([], []).

subm([_|T], S) :-
    subm(T, S).

subm([H|T], [H|S]) :-
    subm(T, S).

% submultimi(L: lista, R: lista de liste)
% (i, o) - determinist
submultimi(L, R) :-
    submultimi(L, [], R).

% colecteaza subliste
submultimi([], Acc, Acc).          % Return the accumulated sublists when the list is empty.
submultimi([_|T], Acc, R) :-       % Skip the current head, continue with the tail.
    submultimi(T, Acc, R).
submultimi([H|T], Acc, R) :-       % Include the current head, recurse with it in the accumulator.
    submultimi(T, [H|Acc], R).
