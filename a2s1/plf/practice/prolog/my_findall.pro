% my_findall(+Template, :Goal, -List)
% Collects all solutions of Goal in List using Template
my_findall(Template, Goal, List) :-
    my_findall(Template, Goal, [], List).  % Start with an empty accumulator

% Base case: if Goal fails, return the accumulator as the result.
my_findall(_, Goal, Acc, Acc) :-
    \+ call(Goal).  % If Goal can't be proven, stop collecting

% Recursive case: if Goal succeeds, add Template to the accumulator and backtrack for more solutions
my_findall(Template, Goal, Acc, List) :-
    call(Goal),  % Call the goal to generate a solution
    append(Acc, [Template], NewAcc),  % Append the current solution to the accumulator
    my_findall(Template, Goal, NewAcc, List).  % Recursively collect more solutions

% Predicate to check if a number is even
even(X) :- X mod 2 =:= 0.

% Example list
list_of_numbers([1, 2, 3, 4, 5, 6]).
