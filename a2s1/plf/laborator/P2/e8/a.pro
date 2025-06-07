% add_one_to_digit(Digit, CarryIn, ResultDigit, CarryOut)
% Adds one to a digit and handles carry.
add_one_to_digit(Digit, CarryIn, ResultDigit, CarryOut) :-
    Temp is Digit + CarryIn,
    ResultDigit is Temp mod 10,  % Keep the last digit only
    CarryOut is Temp div 10.     % Generate a carry if needed (1 or 0)

% add_one(List, Result)
% Adds one to the entire list-represented number.
add_one(List, Result) :-
    reverse(List, RevList),            % Reverse to process from least significant to most significant digit.
    add_one_recursive(RevList, 1, RevResult),  % Start by adding 1 (initial carry of 1).
    reverse(RevResult, Result).        % Reverse back to get the correct order.

% add_one_recursive(List, CarryIn, Result)
% Recursive helper predicate to add one with carry propagation.
add_one_recursive([], 0, []).          % Base case: no carry left, empty list.
add_one_recursive([], 1, [1]).         % If there's a carry left after all digits, add it as the most significant digit.
add_one_recursive([H|T], CarryIn, [ResultDigit|ResultRest]) :-
    add_one_to_digit(H, CarryIn, ResultDigit, CarryOut),
    add_one_recursive(T, CarryOut, ResultRest).
