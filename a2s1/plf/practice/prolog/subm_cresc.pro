


negative([E], [E]):- E<0.
negative(Rez, [_|T]):-!,negative(Rez, T).
negative([E|Rez], [E|T]):- E<0,negative(Rez, T).

