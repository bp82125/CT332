filter_smaller([], _, []) :- !.
filter_smaller([H | T], N, [H | R]) :- H < N, filter_smaller(T, N, R), !.
filter_smaller([_ | T], N, R) :- filter_smaller(T, N, R).

/*
    ?- filter_smaller([1,2,3,4,5,6,7,8,9], 5, R).
    R = [1, 2, 3, 4].
*/