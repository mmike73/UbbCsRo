% cmmdc(A: interg, B: intreg, C: intref)
% (i, i, o) - determinist
cmmdc(A, 0, A).

cmmdc(0, B, B).

cmmdc(A, B, C) :-
    A < B,
    B1 is B mod A,
    cmmdc(A, B1, C).

cmmdc(A, B, C) :-
    A >= B,
    A1 is A mod B,
    cmmdc(B, A1, C).

% cmmmc(A, B, C)
% (i, i, o) - determinist
cmmmc(A, B, C) :-
    cmmdc(A, B, CMMDC),
    CP is A * B,
    C is CP div CMMDC.

% cmmmc_lista(L: lista, R: intreg) :-
% (i, o) - determinist
cmmmc_lista([], 1).

cmmmc_lista([H|T], R) :-
    cmmmc_lista(T,R1),
    cmmmc(R1, H, R).

