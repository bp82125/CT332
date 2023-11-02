/*thempt([], X, [X]) :- !.
thempt([H|T], X, R) :- thempt(T,X,R1), R = [H|R1].

noids(L, [], L) :- !.
noids(L1, [H|T], R) :- thempt(L1, H, R1), noids(R1, T, R).*/

noids([], L, L) :- !.
noids([H|T], L2, [H|T3]) :- noids(T, L2, T3).