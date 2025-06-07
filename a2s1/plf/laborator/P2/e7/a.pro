% multiply_digit(Digit, Multiplier, CarryIn, ResultDigit, CarryOut)
% Multiplies a single digit with a multiplier, adds carry, and returns the result digit and new carry.
multiply_digit(Digit, Multiplier, CarryIn, ResultDigit, CarryOut) :-
    Temp is Digit * Multiplier + CarryIn,
    ResultDigit is Temp mod 10,  % Get the last digit
    CarryOut is Temp div 10.     % Carry for the next operation

% multiply_list(List, Multiplier, Result)
% Multiplies each digit in the list by the multiplier, handling carry across digits.
multiply_list([], _, 0, []). % Base case: no carry and empty list gives empty result.
multiply_list([], _, Carry, [Carry]) :- Carry > 0. % Add remaining carry as the last digit if needed.
multiply_list([H|T], Multiplier, CarryIn, [ResultDigit|ResultRest]) :-
    multiply_digit(H, Multiplier, CarryIn, ResultDigit, CarryOut),
    multiply_list(T, Multiplier, CarryOut, ResultRest).

% product_with_digit(List, Multiplier, Result)
% Wrapper predicate to multiply a list-represented number by a single digit.
product_with_digit(List, Multiplier, Result) :-
    reverse(List, RevList),                   % Reverse list to handle least significant digit first.
    multiply_list(RevList, Multiplier, 0, RevResult), % Multiply with carry starting at 0.
    reverse(RevResult, Result).               % Reverse back to get the correct order.
