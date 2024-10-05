% append_two_list(L1, L2, L3). -> appends L1 and L2 and puts it in L3
append_two_list([], L2, L2). 
append_two_list([X|L1], L2, [X|L3]):-
    append_two_list(L1, L2, L3).


reverse_list_acc([], Res, Res).

reverse_list_acc([H|T], Curr, Res):-
    reverse_list_acc(T, [H|Curr], Res).

% reverse_list(L, Res) -> Res is the reversed List
reverse_list(L, Res):-
    reverse_list_acc(L, [], Res).

list_len_acc([], A, A).

list_len_acc([_|T], A, M):-
    A1 is A + 1,
    list_len_acc(T, A1, M).

% list_len(L, N) -> N is the lenght of the list L
list_len(L, N):-
    list_len_acc(L, 0, N).

% 1. Remove the K'th element from a list.

% remove_at(RemovedElem, List, Index, ResultantList)
% input -> List, Index to remove elem (1 indexed)
% output -> ResultantList, RemovedElem

remove_at_loop(H, [H|T], 1, ResList, VisitedElem):-
    reverse_list(VisitedElem, L1),
    append_two_list(L1, T, ResList).
    
remove_at_loop(RemElem, [H|T], Idx, ResList, VisitedElem):-
    Idx_minus_1 is Idx - 1,
    remove_at_loop(RemElem, T, Idx_minus_1, ResList, [H|VisitedElem]).

remove_at(RemElem, L, Idx, ResList):-
    remove_at_loop(RemElem, L, Idx, ResList, []).

% ?- remove_at(X, [a,b,c,d], 2, R).
% X = b,
% R = [a, c, d] .

% ?- remove_at(X, [a,b,c,d], 5, R).
% false.

% 2. Extract a given number of randomly selected elements from a list.
% The selected items shall be put into a result list.
% Hint: Use the built-in random number generator random/2 and the result of
% problem P1.

rnd_select_loop(_, 0, Res, Res).

rnd_select_loop(L, ResListLen, Res, SelectedElem):-
    list_len(L, L_Len),
    random_between(1, L_Len, RandomIdx),
    remove_at(RemovedElem, L, RandomIdx, RemainingList),
    ResListLen_Minus_1 is ResListLen - 1,
    rnd_select_loop(RemainingList, ResListLen_Minus_1, Res, [RemovedElem|SelectedElem]).
    

%rnd_select(GivenList, ResListLen, ResList) -> ResList will be
% from GivenList of length ResListLen
rnd_select(L, ResListLen, Res):-
    rnd_select_loop(L, ResListLen, Res, []).

% ?- rnd_select([a,b,c,d,e,f,g,h], 3, L).
% L = [c, b, f] .

% ?- rnd_select([a,b,c,d,e,f,g,h], 3, L).
% L = [g, c, e] .

% 3. Generate a random permutation of the elements of a list.
% Hint: Use the solution of problem P2.

rnd_permu(L, Res):-
    list_len(L, L_Len),
    rnd_select(L, L_Len, Res).

% ?- rnd_permu([a,b,c,d,e,f],L).
% {L = [b,a,d,c,e,f]}

% ?- rnd_permu([a,b,c,d,e,f],L).
% L = [e, b, c, f, d, a] .

% 4. Generate the combinations of K distinct objects chosen from the N
% elements of a list
% In how many ways can a committee of 3 be chosen from a group of 12
% people? We all know that there are C(12,3) = 220 possibilities (C(N,K)
% denotes the well-known binomial coefficients). For pure mathematicians,
% this result may be great. But we want to really generate all the possibilities
% (via backtracking).
% Example:
% ?- combination(3,[a,b,c,d,e,f],L).
% {L = [a,b,c]} ;
% {L = [a,b,d]} ;
% {L = [a,b,e]} ; ...

combination_loop(0, _, Res, SelectedElem):-
    !, reverse_list(SelectedElem, Res).

% we either pick the element
combination_loop(ResLen, [H|T], Res, SelectedElem):-
    ResLen_Minus_1 is ResLen - 1,
    combination_loop(ResLen_Minus_1, T, Res, [H|SelectedElem]).

% or we dont
combination_loop(ResLen, [_|T], Res, SelectedElem):-
    combination_loop(ResLen, T, Res, SelectedElem).

combination(ResLen, L, Res):-
    combination_loop(ResLen, L, Res, []).

% ?- combination(1,[a,b,c,d,e,f],L).
% L = [a] ;
% L = [b] ;
% L = [c] ;
% L = [d] ;
% L = [e] ;
% L = [f] ;
% false.

% ?- combination(3,[a,b,c,d,e,f],L).
% L = [a, b, c] ;
% L = [a, b, d] ;
% L = [a, b, e] ;
% L = [a, b, f] ;
% L = [a, c, d] ;
% L = [a, c, e] ;
% L = [a, c, f] ;
% L = [a, d, e] ;
% L = [a, d, f] ;
% L = [a, e, f] ;
% L = [b, c, d] ;
% L = [b, c, e] ;
% L = [b, c, f] ;
% L = [b, d, e] ;
% L = [b, d, f] ;
% L = [b, e, f] ;
% L = [c, d, e] ;
% L = [c, d, f] ;
% L = [c, e, f] ;
% L = [d, e, f] ;
% false.

% ?- combination(5,[a,b,c,d,e,f],L).
% L = [a, b, c, d, e] ;
% L = [a, b, c, d, f] ;
% L = [a, b, c, e, f] ;
% L = [a, b, d, e, f] ;
% L = [a, c, d, e, f] ;
% L = [b, c, d, e, f] ;
% false.

% 5. Implement Permutation Sort.

% is_ascending(L) -> give true if L is sorted in ascending order
is_ascending([]).
is_ascending([_]).
is_ascending([X|[Y|Rest]]):-
    X =< Y,
    is_ascending([Y|Rest]).

permutation_sort(L, Res):-
    permutation(L, Res),
    is_ascending(Res).

% ?- permutation_sort([3,2,1,4],X).
% X = [1, 2, 3, 4] .

% ?- permutation_sort([3,2,1,4,3],X).
% X = [1, 2, 3, 3, 4] .

% 6. Implement Bubble Sort.

bubblesort_swap([X|[Y|T1]],[Y|[X|T1]]):-
    Y<X,!.

bubblesort_swap([X|T1],[X|T2]):- 
    bubblesort_swap(T1,T2).

bubblesort(List, SortedList) :-
    bubblesort_swap(List, List1), !,
    bubblesort(List1, SortedList).

bubblesort(List, List).

% ?- bubblesort([1,2,3,1], X).
% X = [1, 1, 2, 3].

% ?- bubblesort([1,2,3,1,5,2], X).
% X = [1, 1, 2, 2, 3, 5].

% 7. Implement Selection Sort.

% selection_smaller(X, L) -> true if X is smaller than every elem of L
selection_smaller(_, []).
selection_smaller(X, [H|T]):-
    X =< H,
    selection_smaller(X, T).

% selection_least(X, L, R) -> select the least elem X from L, remaining elem in R
selection_least(_, [], []).

selection_least(X, L, R):-
    select(X, L, R),
    selection_smaller(X, R).

selection_sort([],[]).
selection_sort(L, [H|T]):-
    selection_least(H, L, R),
    selection_sort(R, T).

% ?- selection_sort([1,2,3,1,5,2], X).
% X = [1, 1, 2, 2, 3, 5] .

% ?- selection_sort([1,2,3,1,5,2, 100, 1], X).
% X = [1, 1, 1, 2, 2, 3, 5, 100] .

% 8. Implement Insertion Sort.

% insertion_insert(X, L, Res) -> insert X in L for such that the resultant list R is sorted
insertion_insert(X, [], [X]).

insertion_insert(X, [H|T], [X|[H|T]]):-
    X =< H, !.

insertion_insert(X, [H|T], [H|T1]):-
    X > H,
    insertion_insert(X, T, T1).

insertion_sort([], []).

insertion_sort([H|T], L):-
    insertion_sort(T, L1),
    insertion_insert(H, L1, L).

% ?- insertion_sort([5,3,2,4,1], Res).
% Res = [1, 2, 3, 4, 5] .

% ?- insertion_sort([5,3,100,2,4,1], Res).
% Res = [1, 2, 3, 4, 5, 100] .

% 9. Implement Merge Sort.

% merge_sort_divide(L, L1, L2) -> divide L into near equal length list L1 and L2
merge_sort_divide([], [], []).

merge_sort_divide([X], [X], []).

merge_sort_divide([X|[Y|T]], [X|L1], [Y|L2]):-
    merge_sort_divide(T, L1, L2).

% merge_sort_merge(L1, L2, Res) -> merge L1 and L2 in Res such that Res is sorted
% NOTE: L1 and L2 re also sorted input
merge_sort_merge([],[],[]).

merge_sort_merge([X|Rest], [], [X|Rest]).

merge_sort_merge([], [Y|Rest], [Y|Rest]).

merge_sort_merge([X|L1], [Y|L2], [X|L3]):-
    X < Y, !,
    merge_sort_merge(L1, [Y|L2], L3).

merge_sort_merge([X|L1], [Y|L2], [Y|L3]):-
    X > Y, !,
    merge_sort_merge([X|L1], L2, L3).

merge_sort_merge([X|L1], [Y|L2], [X|[Y|L3]]):-
    X = Y, 
    merge_sort_merge(L1, L2, L3).

merge_sort([], []).

merge_sort([X], [X]).

merge_sort(L, M):-
    merge_sort_divide(L, L1, L2),
    merge_sort(L1, L1Sorted),
    merge_sort(L2, L2Sorted),
    merge_sort_merge(L1Sorted, L2Sorted, M).

% ?- merge_sort([2,1], X).
% X = [1, 2] .

% ?- merge_sort([1,6,2,9,3,1], X).
% X = [1, 1, 2, 3, 6, 9] .

% 10. Implement Quick Sort using Accumulator.

% quick_sort_partition(T, Lt, H, Gt) -> partition T into Lt, H, Gt 
% where H is the first elem of T, Lt is the list of elem less than H
% and Gt is the lis tof elem greater than H
quick_sort_partition([], [], _, []).

quick_sort_partition([X|T], [X|TLt], H, Gt):-
    X =< H, !,
    quick_sort_partition(T, TLt, H, Gt).

quick_sort_partition([X|T], Lt, H, [X|TGt]):-
    X > H,
    quick_sort_partition(T, Lt, H, TGt).

quick_sort_acc([], A, A).

quick_sort_acc([H|T], A, L1):-
    quick_sort_partition(T, Lt, H, Gt),
    quick_sort_acc(Gt, A, GtSorted),
    quick_sort_acc(Lt, [H|GtSorted], L1).

quick_sort(L, L1):-
    quick_sort_acc(L, [], L1).

% ?- quick_sort([1,2,3,6,4], X).
% X = [1, 2, 3, 4, 6].

% ?- quick_sort([1,2,3, 89, 3, 8, 2], X).
% X = [1, 2, 2, 3, 3, 8, 89].

% 11. Implement Quick Sort without Accumulator.

quick_sort_no_acc([], []).

quick_sort_no_acc([X], [X]).

quick_sort_no_acc([H|T], L1):-
    quick_sort_partition(T, Lt, H, Gt),
    quick_sort_no_acc(Lt, LtSorted),
    quick_sort_no_acc(Gt, GtSorted),
    append_two_list(LtSorted, [H], Temp),
    append_two_list(Temp, GtSorted, L1).

% ?- quick_sort_no_acc([1,2,3,7,34,5], X).
% X = [1, 2, 3, 5, 7, 34] .

% ?- quick_sort_no_acc([1,2,3,7,34,5,2], X).
% X = [1, 2, 2, 3, 5, 7, 34] .

% 12. Eliminate consecutive duplicates of list elements.
% If a list contains repeated elements they should be replaced with a single copy
% of the element. The order of the elements should not be changed.
compress([X], [X]).

compress([X|[X|R]], Res):-
    compress([X|R], Res).

compress([X|[Y|R]], [X|Res]):-
    compress([Y|R], Res).

% ?- compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [a, b, c, a, d, e] .

% ?- compress([a,a,a,a,b,c,c,a,a,d,e,e,e,e,f,f,f,f],X).
% X = [a, b, c, a, d, e, f] .

% 13. Run-length encoding of a list.
% Use the result of problem P14 to implement the so-called run-length encoding
% data compression method. Consecutive duplicates of elements are encoded as
% terms [N,E] where N is the number of duplicates of the element E.

encode_loop([X], [X], Count, [[Count_plus_1, X]]):-
    Count_plus_1 is Count + 1.

encode_loop([X|L], [Y|LCompress], Count, [[Count,Y]|Res]):- 
    encode_loop([X|L], LCompress, 0, Res).

encode_loop([X|L], [X|LCompress], Count, Res):-
    Count_plus_1 is Count + 1,
    encode_loop(L, [X|LCompress], Count_plus_1, Res).

encode(L, Res):-
    compress(L, LCompress),
    encode_loop(L, LCompress, 0, Res).

% ?- encode([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [[4, a], [1, b], [2, c], [2, a], [1, d], [4, e]] .

% ?- encode([a,a,a,a,b,c,c,a,a,d,e,e,e,e, f, f, f],X).
% X = [[4, a], [1, b], [2, c], [2, a], [1, d], [4, e], [3, f]] .

% 14. Modified run-length encoding.
% Modify the result of problem P15 in such a way that if an element has no
% duplicates it is simply copied into the result list. Only elements with duplicates
% are transferred as [N,E] terms.

encode_modified_loop([[1, X]], [X]).

encode_modified_loop([X], [X]).

encode_modified_loop([[1, X]|Rest], [X|L]):-
    encode_modified_loop(Rest, L).

encode_modified_loop([X|Rest], [X|L]):-
    encode_modified_loop(Rest, L).

encode_modified(L, Res):-
    encode(L, LEncoded),
    encode_modified_loop(LEncoded, Res).

% ?- encode_modified([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% [[4,a],[1,b],[2,c],[2,a],[1,d],[4,e]]
% X = [[4, a], b, [2, c], [2, a], d, [4, e]] .

% ?- encode_modified([a,a,a,a,b,c,c,a,a,d,e,e,e,e,f],X).
% [[4,a],[1,b],[2,c],[2,a],[1,d],[4,e],[1,f]]
% X = [[4, a], b, [2, c], [2, a], d, [4, e], f] .

% 15. Decode a run-length encoded list.
% Given a run-length code list generated as specified in problem P16. Construct
% its uncompressed version.

% not working
% decode_modified(L, Res):-
%     encode_modified(Res, L).

gen_num(X, 1, [X]).
gen_num(X, Num, [X|L1]):-
    Num_minus_1 is Num - 1,
    gen_num(X, Num_minus_1, L1).

decode_modified([[Num, X]], Res):-
    gen_num(X, Num, Res).

decode_modified([X], [X]).

decode_modified([[Num, X]|L], Res):-
    gen_num(X, Num, ResLeft),
    decode_modified(L, ResRight),
    append_two_list(ResLeft, ResRight, Res).

decode_modified([X|L], [X|L1]):-
        decode_modified(L, L1).

% ?- decode_modified([[2, a], b, [2, c], [2, a],  f], X).
% X = [a, a, b, c, c, a, a, f] .

% ?- decode_modified([[2,a], b, [3,c]], X).
% X = [a, a, b, c, c, c] .