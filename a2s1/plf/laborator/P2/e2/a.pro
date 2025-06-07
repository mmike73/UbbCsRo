% minimum(List, Min)
minimum([Min], Min). % Base case: a single-element list
minimum([H|T], Min) :-
    minimum(T, TempMin), % Recursive call to find min of the tail
    Min is min(H, TempMin). % Min is the smaller of the head or the min of the tail

% Predicate to remove the first occurrence of an element from a list
% remove(Element, List, ResultList)
remove(_, [], []). % Base case: empty list
remove(E, [E|T], T). % Case: found element to remove
remove(E, [H|T], [H|R]) :-
    E \= H, % Keep head if it doesn't match the element to remove
    remove(E, T, R). % Recursive call to continue through the list

% Predicate to sort the list using selection sort
% sortwd(List, SortedList)
sortwd([], []). % Base case: empty list is already sorted
sortwd(L, [Min|SortedRest]) :-
    minimum(L, Min),          % Find the minimum element
    remove(Min, L, Rest),     % Remove the minimum from the original list
    sortwd(Rest, SortedRest). % Recursively sort the remaining elements
