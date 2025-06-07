% sterg(List, Result)
% Main predicate to remove all consecutive sequences.
sterg([], []).

% If the list has only one element, keep it (no sequence possible).
sterg([X], [X]).

% Case 1: Start of a consecutive sequence
% If the next element is consecutive to the current one, skip to the end of the sequence.
sterg([X, Y | T], Result) :-
    Y =:= X + 1,                  % Check if Y is consecutive to X
    skip_consecutive([X, Y | T], Rest), % Skip the entire sequence
    sterg(Rest, Result).          % Continue processing with the remaining elements

% Case 2: No consecutive sequence
% If the next element is not consecutive, include X in the result and continue.
sterg([X, Y | T], [X | Result]) :-
    Y =\= X + 1,                  % X and Y are not consecutive
    sterg([Y | T], Result).       % Continue processing the rest of the list

% skip_consecutive(List, Rest)
% Helper predicate that skips a sequence of consecutive numbers.
skip_consecutive([X, Y | T], Rest) :-
    Y =:= X + 1,                  % If Y is consecutive to X
    skip_consecutive([Y | T], Rest). % Recursively skip until sequence ends

% Base case: No more consecutive elements, return the rest of the list.
skip_consecutive([X], [X]).
skip_consecutive([X, Y | T], [Y | T]) :-
    Y =\= X + 1.
