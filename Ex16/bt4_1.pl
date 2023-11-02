thempt([], X, [X]) :- !.
thempt([H|T], X, R) :- thempt(T,X,R1), R = [H|R1].
