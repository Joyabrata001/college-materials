/**
 *
 * is_member/2 predicate returns true if X is a member of list L
 *  
 * @param X the element to search
 * @param L the list to search in  */
is_member(X, [X]).
is_member(X, [X | _]).
is_member(X, [_ | Rest]):-
    is_member(X, Rest).

% range(Low, High, Res) -> Res is [Low, Low+1, ..., High]
range(High, High, [High]).
range(Low, High, [Low|L1]):-
    Low =< High,
    Low_plus_1 is Low + 1,
    range(Low_plus_1, High, L1).

% append_two_list(L1, L2, L3). -> appends L1 and L2 and puts it in L3
append_two_list([], L2, L2). 
append_two_list([X|L1], L2, [X|L3]):-
    append_two_list(L1, L2, L3).

% 1. To find factorial N using accumulator.
factorial_acc(0, Res, Res).

factorial_acc(X, Curr, Res):-
    X_minus_1 is X - 1, 
    NextCurr is Curr*X,
    factorial_acc(X_minus_1, NextCurr, Res).

% factorial(N, X) -> X is N!
factorial(N, X):-
    factorial_acc(N, 1, X).

% ?- factorial(0, X).
% X = 1 .

% ?- factorial(5, X).
% X = 120 .

% ?- factorial(100, X).
% X = 93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000 .

% 2. To find length of a list using accumulator.

list_len_acc([], A, A).

list_len_acc([_|T], A, M):-
    A1 is A + 1,
    list_len_acc(T, A1, M).

% list_len(L, N) -> N is the lenght of the list L
list_len(L, N):-
    list_len_acc(L, 0, N).

% ?- list_len([a,v,s,f,d], X).
% X = 5.

% ?- range(1, 100000, X), list_len(X, N).
% X = [1, 2, 3, 4, 5, 6, 7, 8, 9|...],
% N = 100000 .

% 3. To remove duplicate elements from a list using accumulator.

remove_duplicate_acc([], A, A).

remove_duplicate_acc([H|T], A, M):-
    is_member(H, A), !, 
    remove_duplicate_acc(T, A, M).

remove_duplicate_acc([H|T], A, M):-
    remove_duplicate_acc(T, [H|A], M).
    
remove_duplicate(L, M):-
    remove_duplicate_acc(L, [], M).

% ?- remove_duplicate([a,a,b,c], X).
% X = [c, b, a].

% ?- remove_duplicate([a,a,b,c,d,c], X).
% X = [d, c, b, a].

% 4. To remove duplicate elements from a list without using accumulator.
remove_duplicate_without_acc([], []).

remove_duplicate_without_acc([X|L], L1):-
    is_member(X, L), !,
    remove_duplicate_without_acc(L, L1).

remove_duplicate_without_acc([X|L], [X|L1]):-
    remove_duplicate_without_acc(L, L1).

% ?- remove_duplicate_without_acc([a,a,b,c,d,c], X).
% X = [a, b, d, c].

% ?- remove_duplicate_without_acc([a,a,b,c,d,c,c,c,c], X).
% X = [a, b, d, c].

% 5. To reverse a list using accumulator.

reverse_list_acc([], Res, Res).

reverse_list_acc([H|T], Curr, Res):-
    reverse_list_acc(T, [H|Curr], Res).

reverse_list(L, Res):-
    reverse_list_acc(L, [], Res).

% ?- reverse_list([1,2,3], X).
% X = [3, 2, 1].

% ?- range(1,7,L), reverse_list(L, X).
% L = [1, 2, 3, 4, 5, 6, 7],
% X = [7, 6, 5, 4, 3, 2, 1] .

% 6. Next Higher Permutation.
% A positive integer is represented by a list of decimal digits. Its next
% higher permutation is defined to be the next greater integer composed of
% exactly the same digits. For example, the next higher permutation of
% 123542 is 124235.
% Write 
% a) a declarative Prolog program

% higher(L1, L) return true if L1 is higher than L
higher([H1|_], [H|_]):-
    H1 > H.

higher([H|T1], [H|T]):-
    higher(T1, T).
    
% true if L1 is higher permutation than L
higher_permutation(L1, L):-
    permutation(L, L1), %inbuilt function
    higher(L1, L).

% return true if L1 is not the next higher permutation of L
far_higher_permutation(L1, L):-
    higher_permutation(L1, L),
    higher_permutation(L2, L),
    higher(L1, L2).

% L1 is the next higher permutation of L
next_higher_permutation(L, L1):-
    higher_permutation(L1, L),
    not(far_higher_permutation(L1, L)).

% ?- next_higher_permutation([1,2,3,4,5], X).
% X = [1, 2, 3, 5, 4] .

% ?- next_higher_permutation([4,5,3,2,1], X).
% X = [5, 1, 2, 3, 4] .

% ?- next_higher_permutation([1,2,5,5,4,2], X).
% X = [1, 4, 2, 2, 5, 5] .

% b) an efficient procedural Prolog program
% that receive a list of decimal digits and return its next 
% higher permutation in a list.

% get_first_number_idx_less_than_its_left(L, Y_Idx, Y) 
% Y is the first digit's idx (1 index) when going from left to right which 
% is less than it's left digit 
get_first_number_idx_less_than_its_left(L, Y_Idx, Y):-
    get_first_number_idx_less_than_its_left_loop(L, Y_Idx, Y, 1).

get_first_number_idx_less_than_its_left_loop([H1|[H2|_]], H2_Idx, H2,H1_Idx):-
    H1 > H2, !, 
    H2_Idx is H1_Idx + 1.

get_first_number_idx_less_than_its_left_loop([_|[H2|L]], Y_Idx, Y, H1_Idx):-
    H2_Idx is H1_Idx + 1,
    get_first_number_idx_less_than_its_left_loop([H2|L], Y_Idx, Y, H2_Idx).

% get_first_number_idx_greater_than_given_Y(L, Y, U_Idx, U)
% U is the first number less than Y when traversing from Left to Right
% U_Idx is 1 indexed
get_first_number_idx_greater_than_given_Y(L, Y, U_Idx, U):-
    get_first_number_idx_greater_than_given_Y_loop(L, Y, U_Idx, U, 1).

get_first_number_idx_greater_than_given_Y_loop([H|_], Y, H_Idx, H, H_Idx):-
    H > Y.

get_first_number_idx_greater_than_given_Y_loop([_|T], Y, U_Idx, U, H_Idx):-
    Next_Idx is H_Idx + 1,
    get_first_number_idx_greater_than_given_Y_loop(T, Y, U_Idx, U, Next_Idx).

% set_element_at(L, Idx, Val, Res)
% Res will be same as L, just the data at Idx location(1 indexed) will be replaced by Val
set_element_at([_|T], 1, Val, [Val|T]).

set_element_at([H|T], Idx, Val, [H|T_Res]):-
    Idx_minus_1 is Idx - 1,
    set_element_at(T, Idx_minus_1, Val, T_Res).

% swap(L, A_Idx, B_Idx, Res)
% R is same as L, but data at A_Idx and B_Idx is swapped
% A_Idx and B_Idx are 1 indexed
% A_Idx is the idx of first element going from Left to RIght
% B_Idx is the idx of second element going from Left to RIght
swap(L, A_Idx, A_data, B_Idx, B_data,Res):- 
    set_element_at(L, A_Idx, B_data, L1),
    set_element_at(L1, B_Idx, A_data, Res).

% reverse_left_of_idx(L, Idx, Res)
% Res is same as L, just that the sublist left of Idx is reversed
reverse_left_of_idx(L, Idx, Res):-
    Left_Sublist_Len is Idx - 1,
    append_two_list(L1, L2, L),
    list_len(L1, Left_Sublist_Len),
    reverse_list(L1, L1_Rev),
    append_two_list(L1_Rev, L2, Res).

next_higher_permutation_iterative(L, Res):-
    reverse_list(L, L_Rev),
    get_first_number_idx_less_than_its_left(L_Rev, Y_Idx, Y),
    get_first_number_idx_greater_than_given_Y(L_Rev, Y, U_Idx, U),
    swap(L_Rev, Y_Idx, Y, U_Idx, U, L_Swap),
    reverse_left_of_idx(L_Swap, Y_Idx, Res_Rev),
    reverse_list(Res_Rev, Res).

% ?- next_higher_permutation_iterative([1,2,3,4,5], X).
% X = [1, 2, 3, 5, 4] .

% ?- next_higher_permutation_iterative([4,5,3,2,1], X).
% X = [5, 1, 2, 3, 4] .

% ?- next_higher_permutation_iterative([1,2,5,5,4,2], X).
% X = [1, 4, 2, 2, 5, 5] .

% 7. Eight Queens’ Problem.
% Eight Queens are to be placed in an 8x8 chess board such that no queen
% attack each other.
% Write a Prolog program to obtain solution(s) of Eight Queen Problem.

eight_queen_template([1/_, 2/_, 3/_, 4/_, 5/_, 6/_, 7/_, 8/_]).

eight_queen_no_attack(_, []).

eight_queen_no_attack(X/Y, [X1/Y1|Others]):-
    Y =\= Y1,
    (X-X1)=\=(Y-Y1),
    (X-X1)=\=(Y1-Y),
    eight_queen_no_attack(X/Y, Others).

eight_queen([]).

eight_queen([X/Y|Others]):-
    is_member(Y, [1,2,3,4,5,6,7,8]),
    eight_queen(Others),
    eight_queen_no_attack(X/Y, Others).

% ?- eight_queen_template(X), eight_queen(X).
% X = [1/1, 2/5, 3/8, 4/6, 5/3, 6/7, 7/2, 8/4] ;
% X = [1/1, 2/6, 3/8, 4/3, 5/7, 6/4, 7/2, 8/5] ;
% X = [1/1, 2/7, 3/4, 4/6, 5/8, 6/2, 7/5, 8/3] ;
% X = [1/1, 2/7, 3/5, 4/8, 5/2, 6/4, 7/6, 8/3] ;
% X = [1/2, 2/4, 3/6, 4/8, 5/3, 6/1, 7/7, 8/5] ;
% X = [1/2, 2/5, 3/7, 4/1, 5/3, 6/8, 7/6, 8/4] ;
% X = [1/2, 2/5, 3/7, 4/4, 5/1, 6/8, 7/6, 8/3] ;
% X = [1/2, 2/6, 3/1, 4/7, 5/4, 6/8, 7/3, 8/5] ;
% X = [1/2, 2/6, 3/8, 4/3, 5/1, 6/4, 7/7, 8/5] ;
% X = [1/2, 2/7, 3/3, 4/6, 5/8, 6/5, 7/1, 8/4] ;
% X = [1/2, 2/7, 3/5, 4/8, 5/1, 6/4, 7/6, 8/3] ;
% X = [1/2, 2/8, 3/6, 4/1, 5/3, 6/5, 7/7, 8/4] ;
% X = [1/3, 2/1, 3/7, 4/5, 5/8, 6/2, 7/4, 8/6] ;
% X = [1/3, 2/5, 3/2, 4/8, 5/1, 6/7, 7/4, 8/6] ;
% X = [1/3, 2/5, 3/2, 4/8, 5/6, 6/4, 7/7, 8/1] ;
% X = [1/3, 2/5, 3/7, 4/1, 5/4, 6/2, 7/8, 8/6] ;
% X = [1/3, 2/5, 3/8, 4/4, 5/1, 6/7, 7/2, 8/6] ;
% X = [1/3, 2/6, 3/2, 4/5, 5/8, 6/1, 7/7, 8/4] ;
% X = [1/3, 2/6, 3/2, 4/7, 5/1, 6/4, 7/8, 8/5] ;
% X = [1/3, 2/6, 3/2, 4/7, 5/5, 6/1, 7/8, 8/4] ;
% X = [1/3, 2/6, 3/4, 4/1, 5/8, 6/5, 7/7, 8/2] ;
% X = [1/3, 2/6, 3/4, 4/2, 5/8, 6/5, 7/7, 8/1] ;
% X = [1/3, 2/6, 3/8, 4/1, 5/4, 6/7, 7/5, 8/2] ;
% X = [1/3, 2/6, 3/8, 4/1, 5/5, 6/7, 7/2, 8/4] ;
% X = [1/3, 2/6, 3/8, 4/2, 5/4, 6/1, 7/7, 8/5] ;
% X = [1/3, 2/7, 3/2, 4/8, 5/5, 6/1, 7/4, 8/6] ;
% X = [1/3, 2/7, 3/2, 4/8, 5/6, 6/4, 7/1, 8/5] ;
% X = [1/3, 2/8, 3/4, 4/7, 5/1, 6/6, 7/2, 8/5] ;
% X = [1/4, 2/1, 3/5, 4/8, 5/2, 6/7, 7/3, 8/6] ;
% X = [1/4, 2/1, 3/5, 4/8, 5/6, 6/3, 7/7, 8/2] ;
% X = [1/4, 2/2, 3/5, 4/8, 5/6, 6/1, 7/3, 8/7] ;
% X = [1/4, 2/2, 3/7, 4/3, 5/6, 6/8, 7/1, 8/5] ;
% X = [1/4, 2/2, 3/7, 4/3, 5/6, 6/8, 7/5, 8/1] ;
% X = [1/4, 2/2, 3/7, 4/5, 5/1, 6/8, 7/6, 8/3] ;
% X = [1/4, 2/2, 3/8, 4/5, 5/7, 6/1, 7/3, 8/6] ;
% X = [1/4, 2/2, 3/8, 4/6, 5/1, 6/3, 7/5, 8/7] ;
% X = [1/4, 2/6, 3/1, 4/5, 5/2, 6/8, 7/3, 8/7] ;
% X = [1/4, 2/6, 3/8, 4/2, 5/7, 6/1, 7/3, 8/5] ;
% X = [1/4, 2/6, 3/8, 4/3, 5/1, 6/7, 7/5, 8/2] ;
% X = [1/4, 2/7, 3/1, 4/8, 5/5, 6/2, 7/6, 8/3] ;
% X = [1/4, 2/7, 3/3, 4/8, 5/2, 6/5, 7/1, 8/6] ;
% X = [1/4, 2/7, 3/5, 4/2, 5/6, 6/1, 7/3, 8/8] ;
% X = [1/4, 2/7, 3/5, 4/3, 5/1, 6/6, 7/8, 8/2] ;
% X = [1/4, 2/8, 3/1, 4/3, 5/6, 6/2, 7/7, 8/5] ;
% X = [1/4, 2/8, 3/1, 4/5, 5/7, 6/2, 7/6, 8/3] ;
% X = [1/4, 2/8, 3/5, 4/3, 5/1, 6/7, 7/2, 8/6] ;
% X = [1/5, 2/1, 3/4, 4/6, 5/8, 6/2, 7/7, 8/3] ;
% X = [1/5, 2/1, 3/8, 4/4, 5/2, 6/7, 7/3, 8/6] ;
% X = [1/5, 2/1, 3/8, 4/6, 5/3, 6/7, 7/2, 8/4] ;
% X = [1/5, 2/2, 3/4, 4/6, 5/8, 6/3, 7/1, 8/7] ;
% X = [1/5, 2/2, 3/4, 4/7, 5/3, 6/8, 7/6, 8/1] ;
% X = [1/5, 2/2, 3/6, 4/1, 5/7, 6/4, 7/8, 8/3] ;
% X = [1/5, 2/2, 3/8, 4/1, 5/4, 6/7, 7/3, 8/6] ;
% X = [1/5, 2/3, 3/1, 4/6, 5/8, 6/2, 7/4, 8/7] ;
% X = [1/5, 2/3, 3/1, 4/7, 5/2, 6/8, 7/6, 8/4] ;
% X = [1/5, 2/3, 3/8, 4/4, 5/7, 6/1, 7/6, 8/2] ;
% X = [1/5, 2/7, 3/1, 4/3, 5/8, 6/6, 7/4, 8/2] ;
% X = [1/5, 2/7, 3/1, 4/4, 5/2, 6/8, 7/6, 8/3] ;
% X = [1/5, 2/7, 3/2, 4/4, 5/8, 6/1, 7/3, 8/6] ;
% X = [1/5, 2/7, 3/2, 4/6, 5/3, 6/1, 7/4, 8/8] ;
% X = [1/5, 2/7, 3/2, 4/6, 5/3, 6/1, 7/8, 8/4] ;
% X = [1/5, 2/7, 3/4, 4/1, 5/3, 6/8, 7/6, 8/2] ;
% X = [1/5, 2/8, 3/4, 4/1, 5/3, 6/6, 7/2, 8/7] ;
% X = [1/5, 2/8, 3/4, 4/1, 5/7, 6/2, 7/6, 8/3] ;
% X = [1/6, 2/1, 3/5, 4/2, 5/8, 6/3, 7/7, 8/4] ;
% X = [1/6, 2/2, 3/7, 4/1, 5/3, 6/5, 7/8, 8/4] ;
% X = [1/6, 2/2, 3/7, 4/1, 5/4, 6/8, 7/5, 8/3] ;
% X = [1/6, 2/3, 3/1, 4/7, 5/5, 6/8, 7/2, 8/4] ;
% X = [1/6, 2/3, 3/1, 4/8, 5/4, 6/2, 7/7, 8/5] ;
% X = [1/6, 2/3, 3/1, 4/8, 5/5, 6/2, 7/4, 8/7] ;
% X = [1/6, 2/3, 3/5, 4/7, 5/1, 6/4, 7/2, 8/8] ;
% X = [1/6, 2/3, 3/5, 4/8, 5/1, 6/4, 7/2, 8/7] ;
% X = [1/6, 2/3, 3/7, 4/2, 5/4, 6/8, 7/1, 8/5] ;
% X = [1/6, 2/3, 3/7, 4/2, 5/8, 6/5, 7/1, 8/4] ;
% X = [1/6, 2/3, 3/7, 4/4, 5/1, 6/8, 7/2, 8/5] ;
% X = [1/6, 2/4, 3/1, 4/5, 5/8, 6/2, 7/7, 8/3] ;
% X = [1/6, 2/4, 3/2, 4/8, 5/5, 6/7, 7/1, 8/3] ;
% X = [1/6, 2/4, 3/7, 4/1, 5/3, 6/5, 7/2, 8/8] ;
% X = [1/6, 2/4, 3/7, 4/1, 5/8, 6/2, 7/5, 8/3] ;
% X = [1/6, 2/8, 3/2, 4/4, 5/1, 6/7, 7/5, 8/3] ;
% X = [1/7, 2/1, 3/3, 4/8, 5/6, 6/4, 7/2, 8/5] ;
% X = [1/7, 2/2, 3/4, 4/1, 5/8, 6/5, 7/3, 8/6] ;
% X = [1/7, 2/2, 3/6, 4/3, 5/1, 6/4, 7/8, 8/5] ;
% X = [1/7, 2/3, 3/1, 4/6, 5/8, 6/5, 7/2, 8/4] ;
% X = [1/7, 2/3, 3/8, 4/2, 5/5, 6/1, 7/6, 8/4] ;
% X = [1/7, 2/4, 3/2, 4/5, 5/8, 6/1, 7/3, 8/6] ;
% X = [1/7, 2/4, 3/2, 4/8, 5/6, 6/1, 7/3, 8/5] ;
% X = [1/7, 2/5, 3/3, 4/1, 5/6, 6/8, 7/2, 8/4] ;
% X = [1/8, 2/2, 3/4, 4/1, 5/7, 6/5, 7/3, 8/6] ;
% X = [1/8, 2/2, 3/5, 4/3, 5/1, 6/7, 7/4, 8/6] ;
% X = [1/8, 2/3, 3/1, 4/6, 5/2, 6/5, 7/7, 8/4] ;
% X = [1/8, 2/4, 3/1, 4/3, 5/6, 6/2, 7/7, 8/5] ;
% false.

% 8. Tower of Hanoi Problem.
% The tower of Hanoi is a game played with three poles and a set of N discs.
% The discs are graded in diameter, and fit onto the poles by means of a
% hole cut through the center of each disc. Initially all the discs are on the
% left-hand pole. The object of the game is to move all the discs onto the

% center pole. The right-hand pole can be used as a “spare” pole, temporary
% resting place for discs. Each time a disc is moved from one pole to another, two
% constraints must be observed: only the top disc on a pole can
% be moved, and no disc may be placed on top of a smaller one.
% Write Prolog program to enumerate the moves to transfer N discs from
% the left-hand pole to the center pole.
tower_of_hanoi_print_res([]).
tower_of_hanoi_print_res([H|L]):-
    print(H), nl,
    tower_of_hanoi_print_res(L).

tower_of_hanoi(N):-
    range(1, N, L),
    tower_of_hanoi_recur(L, [], [], []).

% Left, Middle and Right is a list of increasing numbers
% History is a list of visited nodes for DFS check
% tower_of_hanoi_recur(Left, Middle, Right, History)

% CASE 1: only in Left (start case, hence no history check)
tower_of_hanoi_recur([LTop|L], [], [], H):-
    tower_of_hanoi_recur(L, [LTop], [], [([LTop|L], [], [])|H]).

tower_of_hanoi_recur([LTop|L], [], [], H):-
    tower_of_hanoi_recur(L, [], [LTop], [([LTop|L], [], [])|H]).

% CASE 2: only in middle (end case)
tower_of_hanoi_recur([], M, [], H):-
    reverse_list([([], M, [])|H], H_rev),
    tower_of_hanoi_print_res(H_rev).

% CASE 3: only in right
tower_of_hanoi_recur([], [], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([], [], [RTop|R]), H)),
    tower_of_hanoi_recur([RTop], [], R, [([], [], [RTop|R])|H]).

tower_of_hanoi_recur([], [], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([], [], [RTop|R]), H)),
    tower_of_hanoi_recur([], [RTop], R, [([], [], [RTop|R])|H]).

% CASE 4: Right Empty (anyone can put in right)
tower_of_hanoi_recur([LTop|L], [MTop|M], [], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [MTop|M], []), H)),
    tower_of_hanoi_recur([LTop|L], M, [MTop], [([LTop|L], [MTop|M], [])|H]).

tower_of_hanoi_recur([LTop|L], [MTop|M], [], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [MTop|M], []), H)),
    tower_of_hanoi_recur(L, [MTop|M], [LTop], [([LTop|L], [MTop|M], [])|H]).

% CASE 5: Middle Empty (anyone can put in middle)
tower_of_hanoi_recur([LTop|L], [], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [], [RTop|R]), H)),
    tower_of_hanoi_recur(L, [LTop], [RTop|R], [([LTop|L], [], [RTop|R])|H]).

tower_of_hanoi_recur([LTop|L], [], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [], [RTop|R]), H)),
    tower_of_hanoi_recur([LTop|L], [RTop], R, [([LTop|L], [], [RTop|R])|H]).

% CASE 6: Left Empty (anyone can put in left)
tower_of_hanoi_recur([], [MTop|M], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([], [MTop|M], [RTop|R]), H)),
    tower_of_hanoi_recur([MTop], M, [RTop|R], [([], [MTop|M], [RTop|R])|H]).

tower_of_hanoi_recur([], [MTop|M], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([], [MTop|M], [RTop|R]), H)),
    tower_of_hanoi_recur([RTop], [MTop|M], R, [([], [MTop|M], [RTop|R])|H]).

% CASE 7: None Empty (comparision based insertion take place)
tower_of_hanoi_recur([LTop|L], [MTop|M], R, H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [MTop|M], R), H)),
    LTop < MTop, %LTop can go on top of MTop
    tower_of_hanoi_recur(L, [LTop|[MTop|M]], R, [([LTop|L], [MTop|M], R)|H]).
    
tower_of_hanoi_recur([LTop|L], M, [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], M, [RTop|R]), H)),
    LTop < RTop, %LTop can go on top of RTop
    tower_of_hanoi_recur(L, M, [LTop|[RTop|R]], [([LTop|L], M, [RTop|R])|H]).

tower_of_hanoi_recur([LTop|L], [MTop|M], R, H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], [MTop|M], R), H)),
    MTop < LTop, %MTop can go on top of LTop
    tower_of_hanoi_recur([MTop|[LTop|L]], M, R, [([LTop|L], [MTop|M], R)|H]).

tower_of_hanoi_recur(L, [MTop|M], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member((L, [MTop|M], [RTop|R]), H)),
    MTop < RTop, %MTop can go on top of RTop
    tower_of_hanoi_recur(L, M, [MTop|[RTop|R]], [(L, [MTop|M], [RTop|R])|H]).

tower_of_hanoi_recur([LTop|L], M, [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member(([LTop|L], M,  [RTop|R]), H)),
    RTop < LTop, %RTop can go on top of LTop
    tower_of_hanoi_recur([RTop|[LTop|L]], M, R, [([LTop|L], M, [RTop|R])|H]).

tower_of_hanoi_recur(L, [MTop|M], [RTop|R], H):-
    % check if the currect state is not already visited
    not(is_member((L, [MTop|M], [RTop|R]), H)),
    RTop < MTop, %RTop can go on top of MTop
    tower_of_hanoi_recur(L, [RTop|[MTop|M]], R, [(L, [MTop|M], [RTop|R])|H]).

% ?- tower_of_hanoi(1).
% [1],[],[]
% [],[1],[]
% true ;
% [1],[],[]
% [],[],[1]
% [1],[],[]
% [],[1],[]
% true ;
% [1],[],[]
% [],[],[1]
% [],[1],[]
% true ;
% false.

% ?- tower_of_hanoi(2).
% [1,2],[],[]
% [2],[1],[]
% [2],[],[1]
% [],[2],[1]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [2],[],[1]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [1,2],[],[]
% [2],[],[1]
% [],[2],[1]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[1],[]
% [1,2],[],[]
% [2],[],[1]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [],[2],[1]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[2],[1]
% [],[1,2],[]
% true ;
% [1,2],[],[]
% [2],[],[1]
% [1,2],[],[]
% [2],[1],[]
% [],[1],[2]
% [],[],[1,2]
% [1],[],[2]
% [1],[2],[]
% [],[1,2],[]
% true ;
% false.

% 9. There is an old song that goes as follows:
% 99 bottles of coke on the wall
% 99 bottles of coke
% You take one down and pass it around
% 98 bottles of coke on the wall
% and so on,
% until the last verse
% 1 bottle of coke on the wall
% 1 bottle of coke
% You take one down and pass it around
% No bottle of coke on the wall.
% Write a Prolog program cola that receives a positive integer and prints
% the Lyrics of the song. The program should print all the verses, and when
% it gets to the last verse, it must print 1 bottle, not 1 bottles and no bottle
% rather than 0 bottles.
cola(1):-
    write("1 bottle of coke on the wall"), nl,
    write("1 bottle of coke"),nl,
    write("You take one down and pass it around"), nl,
    write("No bottle of coke on the wall.").

cola(N):-
    write(N), write(" bottles of coke on the wall"), nl,
    write(N), write(" bottles of coke"), nl,
    write("You take one down and pass it around"), nl,
    N_minus_1 is N - 1,
    cola(N_minus_1).

% ?- cola(3).
% 3 bottles of coke on the wall
% 3 bottles of coke
% You take one down and pass it around
% 2 bottles of coke on the wall
% 2 bottles of coke
% You take one down and pass it around
% 1 bottle of coke on the wall
% 1 bottle of coke
% You take one down and pass it around
% No bottle of coke on the wall.
% true .

% 10. One way of representing the positive whole numbers is a Prolog terms
% involving the integer 0 and the successor functor s with one argument. Thus, we
% represent 0 by itself, 1 by s (0), 2 by s (s (0)) and so on. Write definitions of
% standard arithmetic operations addition, multiplication and subtraction, given
% the above representation of numbers.
% For example, the predicate plus may be defined to exhibit the following
% behavior.
% ? - plus (s (s (0)), s (s (s (0))), X).
% {X= s (s (s (s (s (0)))))}
% that is, 2+3 = 5.
% Also define the predicate “less than”, “greater than”, “less than equal to” and
% “greater than equal to”.

% Further define arithmetic operations, like integer division, remainder of integer
% division, and square root.

custom_number_addition(0, X, X).
custom_number_addition(s(X), Y, s(Z)):-
    custom_number_addition(X, Y, Z).
% ?- custom_number_addition(s(s(0)), s(s(s(0))), X).
% X = s(s(s(s(s(0))))).

custom_number_subtraction(X, 0, X).
custom_number_subtraction(s(X), s(Y), Z):-
    custom_number_subtraction(X, Y, Z).
% ?- custom_number_subtraction(s(s(s(0))), s(s(0)), X).
% X = s(0) .

custom_number_multiplication(0, _, 0).
custom_number_multiplication(s(X), Y, Z):-
    custom_number_multiplication(X, Y, A),
    custom_number_addition(A, Y, Z).
% ?- custom_number_multiplication(s(s(0)), s(s(s(0))), X).
% X = s(s(s(s(s(s(0)))))).

custom_number_less_than(0, s(_)).
custom_number_less_than(s(X), s(Y)):-
    custom_number_less_than(X, Y).
% ?- custom_number_less_than(s(0), s(s(0))).
% true.

% ?- custom_number_less_than(s(s(0)), s(s(0))).
% false.
custom_number_less_than_equal(0, 0).
custom_number_less_than_equal(0, s(_)).
custom_number_less_than_equal(s(X), s(Y)):-
    custom_number_less_than_equal(X, Y).
% ?- custom_number_less_than_equal(s(0), s(s(0))).
% true.

% ?- custom_number_less_than_equal(s(s(0)), s(s(0))).
% true .

custom_number_greater_than(X, Y):-
    not(custom_number_less_than_equal(X, Y)).
% ?- custom_number_greater_than(s(s(0)), s(0)).
% true.

% ?- custom_number_greater_than(s(s(0)), s(s(0))).
% false.

custom_number_greater_than_equal(X, Y):-
    not(custom_number_less_than(X, Y)).
% ?- custom_number_greater_than_equal(s(s(0)), s(0)).
% true.

% ?- custom_number_greater_than_equal(s(s(0)), s(s(0))).
% true.

% X = Quo*Y + Rem 
custom_number_quotient_remainder_division(X, Y, Quo, Rem):-
    custom_number_multiplication(Quo, Y, A),
    custom_number_addition(A, Rem, X),
    custom_number_less_than(Rem, Y).
% ?- custom_number_quotient_remainder_division(s(s(s(s(s(0))))), s(s(0)), Quo, Rem).
% Quo = s(s(0)),
% Rem = s(0) .

% X = Y*Y
custom_number_square_root(X, Y):-
    custom_number_multiplication(Y, Y, X).
% ?- custom_number_square_root(s(s(s(s(0)))), X).
% X = s(s(0)) .