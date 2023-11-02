replace(I, [Old|T], [New|T], Old, New) :- I == 0, !.
replace(I, [H|T], [H|T1], Old, New) :- I > 0, I1 is I - 1, replace(I1, T, T1, Old, New).

swap(I, J, L1, L2) :-
   replace(I, L1, L3, X, Y),
   replace(J, L3, L2, Y, X).

/*
    ?- swap(3, 5, [1,2,3,4,5,6,7,8,9], L2).
    L2 = [1, 2, 3, 6, 5, 4, 7, 8, 9].
*/