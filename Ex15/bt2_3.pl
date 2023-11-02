anhChiEmRuot(X, Y) :- cha(Z, X), cha(Z, Y), me(T, X), me(T, Y).

anhRuot(X, Y) :- nam(X), anhChiEmRuot(X, Y), lonTuoiHon(X, Y).
chiRuot(X, Y):- nu(X), anhChiEmRuot(X, Y), lonTuoiHon(X, Y).
emTraiRuot(X, Y) :- nam(X), anhChiEmRuot(X, Y), lonTuoiHon(Y, X).
emGaiRuot(X, Y) :- nu(X), anhChiEmRuot(X, Y), lonTuoiHon(Y, X).

chu(X, Y) :- cha(Z, Y), anh_ruot(Z, X).
bacTrai(X, Y) :- cha(Z, Y), anh_ruot(X, Z).
cau(X, Y) :- me(T, Y), (anhRuot(X, T); emTraiRuot(X, T)).

co(X, Y) :- cha(Z, Y), chiRuot(Z, X).
di(X, Y) :- me(T, Y), chiRuot(X, T).
mo(X, Y) :- cau(Z, Y), vo(X, Z).
thim(X, Y) :- chu(Z, Y), vo(X, Z).
bacGai(X, Y) :- bacTrai(Z, Y), vo(X, Z).

ongNoi(X, Y) :- cha(Z, Y), cha(X, Z).
ongNgoai(X, Y) :- me(T, Y), cha(X, T).

baNoi(X, Y) :- cha(Z, Y), me(X, Z).
baNgoai(X, Y) :- me(T, Y), me(X, T).

chaVo(X, Y) :- vo(Z, Y), cha(X, Z).
meVo(X, Y) :- vo(Z, Y), me(X, Z).
chaChong(X, Y) :- chong(Z, Y), cha(X, Z).
meChong(X, Y) :- chong(Z, Y), me(X, Z).