thucan('Ga').
thucan('Tao').
thucan(Y) :- an(X, Y), consong(X).

consong('Bill').

an('Bill', 'Dau phong').
an('John', X) :- thucan(X).
an('Sue', X) :- an('Bill', X).