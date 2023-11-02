c(_, 0, 1) :- !.
c(N, N, 1) :- !.
c(N, R, X) :- N1 is N - 1, R1 is R - 1, c(N1, R1, X1), c(N1, R, X2), X is X1 + X2.
