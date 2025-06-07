% minimum(List, Min)
minimum([Min], Min). % Base case: a single-element list
minimum([H|T], Min) :-
    minimum(T, TempMin), % Recursive call to find min of the tail
    Min is min(H, TempMin). % Min is the smaller of the head or the min of the tail

% Predicate to remove the first occurrence of an element from a list
% remove(Element, List, ResultList)
remove(_, [], []). % Base case: empty list
remove(E, [E|T], R) :-
    remove(E,T, R).
remove(E, [H|T], [H|R]) :-
    E \= H, 
    remove(E, T, R).

% Predicate to sort the list using selection sort
% sortwd(List, SortedList)
sortwd([], []). % Base case: empty list is already sorted
sortwd(L, [Min|SortedRest]) :-
    minimum(L, Min),          
    remove(Min, L, Rest),     
    sortwd(Rest, SortedRest). 
