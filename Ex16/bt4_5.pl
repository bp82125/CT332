sum_odd_nums([], 0) :- !.
sum_odd_nums([X], X) :- !.
sum_odd_nums([X, _|T], Sum) :- sum_odd_nums(T, SumT), Sum is X + SumT.

/*
    ?- sum_odd_nums([1,2,3,4,5], R).
    R = 9.
*/