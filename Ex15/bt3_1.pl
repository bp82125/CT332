luyThua(X, 0, 1) :- !.
luyThua(X, Y, R) :- Y1 is Y - 1, luyThua(X, Y1, R1), R is R1 * X.