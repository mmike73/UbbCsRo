% comb(L: list, K: integer, C: list)
% (i, i, o) - nedeterminist
comb([H|_], 1, [H]).  % Base case: Combination of length 1 is the element itself
comb([_|T], K, C) :-
    comb(T, K, C).  % Skip the current element and continue with the rest
comb([H|T], K, [H|C]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, C).  % Include the element H in the combination and reduce K

% collect_all_combinations(L: list, K: integer, AllCombinations: list)
% Collect all combinations of length K from list L
collect_all_combinations(L, K, AllCombinations) :-
    collect_combinations(L, K, [], AllCombinations).  % Start with an empty accumulator

% collect_combinations(L: list, K: integer, Acc: list, AllCombinations: list)
% Recursively collect all combinations, accumulating the results in Acc
collect_combinations([], _, Acc, Acc).  % If the list is empty, the accumulator is the result
collect_combinations([_|T], K, Acc, AllCombinations) :-
    collect_combinations(T, K, Acc, AllCombinations).  % Skip the current element
collect_combinations([H|T], K, Acc, AllCombinations) :-
    K > 0,
    comb(T, K, C),  % Find a combination of length K in the tail of the list
    collect_combinations(T, K, [C|Acc], AllCombinations).  % Accumulate the result
