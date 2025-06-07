% main predicate to find the longest even sequence
longest_even_sequence(List, Result) :-
    find_sequences(List, [], Sequences),      % Step 1: find all even sequences
    max_sequence(Sequences, [], Result).      % Step 2: find the longest sequence

% find_sequences(List, CurrentSequence, AllSequences)
% Traverses the list and collects all sequences of consecutive even numbers
find_sequences([], [], []).                   % If the list and current sequence are empty, done
find_sequences([], CurrentSequence, [CurrentSequence]) :-
    CurrentSequence \= [].                    % End of list, add remaining sequence if any
find_sequences([H|T], CurrentSequence, Sequences) :-
    0 is H mod 2,                             % Check if H is even
    append(CurrentSequence, [H], NewSeq),     % Add H to the current sequence
    find_sequences(T, NewSeq, Sequences).
find_sequences([H|T], CurrentSequence, [CurrentSequence|Sequences]) :-
    1 is H mod 2,                             % If H is odd, end current sequence
    CurrentSequence \= [],                    % Current sequence must be non-empty to save
    find_sequences(T, [], Sequences).
find_sequences([H|T], [], Sequences) :-
    1 is H mod 2,                             % Skip odd numbers when no current sequence
    find_sequences(T, [], Sequences).

% max_sequence(Sequences, CurrentMax, Result)
% Finds the longest sequence from a list of sequences
max_sequence([], Result, Result).             % If no more sequences, return the max found
max_sequence([Seq|T], CurrentMax, Result) :-
    length(Seq, Len1),                        % Length of the current sequence
    length(CurrentMax, Len2),                 % Length of the current maximum sequence
    (   Len1 > Len2                           % If current sequence is longer
    ->  max_sequence(T, Seq, Result)          % Update max sequence
    ;   max_sequence(T, CurrentMax, Result)   % Else, keep current max
    ).
