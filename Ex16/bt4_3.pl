ptvtle([], []).
ptvtle([X], [X]).
ptvtle([X, _|T1], [X|T2]) :- ptvtle(T1, T2).