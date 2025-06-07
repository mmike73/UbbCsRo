% Main predicate to find the predecessor of a number represented by a list of digits
predecessor([0], []) :- !.  % Special case: the predecessor of 0 is an empty list

predecessor(Digits, Result) :-
    reverse(Digits, RevDigits),              % Reverse to process from the least significant digit
    decrement(RevDigits, RevResult),         % Perform the decrement
    reverse(RevResult, Result).              % Reverse back to get the correct order

% decrement(List, Result)
% Helper predicate to handle the decrement with borrowing
decrement([0|T], [9|R]) :-                   % If the digit is 0, change to 9 and continue borrowing
    decrement(T, R).
decrement([D|T], [D1|T]) :-                  % If the digit is not 0, simply decrement it
    D > 0,
    D1 is D - 1.
