person('Marcus').
pompeian('Marcus').
roman(X) :- pompeian(X).
ruler('Ceasar').
tryToAssasinate(X, Y) :- roman(X), ruler(Y), notLoyalTo(X, Y).
notLoyalTo('Marcus', 'Ceasar').