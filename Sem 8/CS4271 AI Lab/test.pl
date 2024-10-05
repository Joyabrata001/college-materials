reverse_list(L, Ans):-
    reverse_list_acc(L, Ans, []).

reverse_list_acc([], Ans, Ans).

reverse_list_acc([H|T], Ans, Temp):-
    reverse_list_acc(T, Ans, [H|Temp]).

append_list([], L, L).

append_list([H|T], L, [H|L2]):-
    append_list(T, L, L2).

list_len([_], 1).

list_len([_|T], A_plus_1):-
    list_len(T, A),
    A_plus_1 is A + 1.

unfold(L, L1):-
    append_list(Left, B, L),
    append_list(Mid, Right, B),
    list_len(Mid, 1),
    list_len(Left, X),
    list_len(Right, X),
    reverse_list(Left, LeftRev),
    reverse_list(Right, RightRev),
    append_list(LeftRev, Mid, L1Left),
    append_list(L1Left, RightRev, L1).
