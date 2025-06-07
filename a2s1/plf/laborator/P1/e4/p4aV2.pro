/*a. Sa se scrie un predicat care substituie intr-o lista un element printr-o
alta lista.*/

concateneaza([], Lista2, Lista2).

concateneaza([H|Lista1], Lista2, [H|Rez]) :-
    concateneaza(Lista1, Lista2, Rez).

% substituie(indicele elementului de substituit(input), lista cu care substituie(input), rezultat (output))

substituie1(0, [_|T], Lista, AltaLista) :-
    append(Lista, T, AltaLista).

substituie1(IND, [H|T], Lista, [H|T2]) :-
    IND > 0,
    IND1 is IND - 1,
    substituie1(IND1, T, Lista, T2).
