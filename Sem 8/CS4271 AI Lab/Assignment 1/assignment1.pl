% 1. To determine whether the first two elements of a list 
% are same
first_two_same([X|[X|_]]).

% 2. To determine whether a list is not a two-element list.
not_two_element_list([]).
not_two_element_list([_]).
not_two_element_list([_|[_|[_ | _]]]).

% 3. To determine whether two lists are of same length.
equal_length([],[]).
equal_length([_ | L1], [_ | L2]):-
    equal_length(L1, L2).

% 4. To determine length of a list using your own number system.
% length 0 -> 0
% length 1 -> s(0)
% length 2 -> s(s(0))
my_list_length([], 0).
my_list_length([_| Rest], s(L)):-
    my_list_length(Rest, L).

% 5. To determine whether two lists are of same length using 
% the length predicate developed in 4 (previous problem).
equal_length1(L1, L2):-
    my_list_length(L1, X),
    my_list_length(L2, X).

% 6. To find the last element of a list. 
last_element([X], X).
last_element([_ | [B |L1]], X):-
    last_element([B | L1], X).

% 7. To find whether an element is a member of a list.
is_member(X, [X]).
is_member(X, [X | _]).
is_member(X, [_ | Rest]):-
    is_member(X, Rest).

% 8. To find whether two elements are next to each other in 
% a list.
two_elem_next(A, B, [A | [B | _]]):- !.
two_elem_next(A, B, [_ | Rest]):-
    two_elem_next(A, B, Rest).

% 9. To append two lists in a third list.
% append_two_list(L1, L2, L3). -> appends L1 and L2 and puts it in L3
append_two_list([], L2, L2). 
append_two_list([X|L1], L2, [X|L3]):-
    append_two_list(L1, L2, L3).

% 10. To find the last element of a list using append 
% predicate developed in 9
last_element1(L1, X):-
    append_two_list(_, [X], L1).

% 11. To find whether an element is a member of a list using
% append predicate developed in 9
% is_member(X, L1). -> true if X is in L1
is_member1(X, L1):-
    append_two_list(_, [X|_], L1).

% 12. To find whether two elements are next to each other in a list using append predicate
% developed in 9.
% next_each_other(X, Y, L)
next_each_other(X, Y, L):-
    append_two_list(_, [X|[Y|_]], L).

% 13. To reverse a list in another list.
% reverse_list(L, R), R is the resultant
reverse_list([], []).
reverse_list([X|L], L1):-
    reverse_list(L, L2),
    append_two_list(L2, [X], L1).

% 14. To determine whether a list is a palindrome.
% is_palindrome(L) -> give true if palindrome
is_palindrome(L):-
    reverse_list(L, L).

% 15. To find the last but one element of a list.
% last_but_one(L, X) -> X is the last but one element of list L
last_but_one(L, X):-
    append_two_list(_, [X|[_]], L).

% 16. To find the sum of all elements of a list.
% sum_list(L, S) -> S is the sum of all elements of list L
sum_list([], 0).
sum_list([H|T], Sum) :-
   sum_list(T, Rest),
   Sum is H + Rest.

% 17. To find the maximum number from a list.

% max_two_num(X, Y, Z) -> Z is the max number between X and Y
max_two_num(X, Y, X):-
    X >= Y.
max_two_num(X, Y, Y):-
    X =< Y.

% max_list(L, X) -> X is the maximum number of list L
max_list([X], X).
max_list([X | Rest], Max):-
    max_list(Rest, MaxRest),
    max_two_num(X, MaxRest, Max).

% 18. To find gcd of two integers.
% gcd_two_num(X, Y, Z) -> Z is the gcd of X and Y
gcd_two_num(X,Y,G) :- X=Y, G=X.
gcd_two_num(X,Y,G) :- X<Y, Y1 is Y-X, gcd_two_num(X,Y1,G).
gcd_two_num(X,Y,G) :- X>Y ,gcd_two_num(Y,X,G).

% 19. To determine whether a given integer number is prime.
% divisible(X, Y), X is divisible by Y
divisible(X,Y) :- 0 is X mod Y, !.

prime_loop(X, Curr):-
    Curr = X, !.

prime_loop(X, Curr):-
    Curr < X, 
    not(divisible(X, Curr)),
    NextCurr is Curr + 1,
    prime_loop(X, NextCurr), !.

% is_prime(X) -> true if X is prime
is_prime(2) :- true, !.
is_prime(X) :- X < 2,!,false.

is_prime(X) :- 
    prime_loop(X, 2).

% 20. To determine whether two positive integer numbers are co-prime.
% coprime(X, Y) -> true if X and Y are coprime
coprime(X, Y):-
    gcd_two_num(X, Y, 1).

% 21. To determine the prime factors of a given positive integer.
find_smallest_prime_loop(X, Curr, P):-
    is_prime(Curr), 
    divisible(X, Curr),  
    P is Curr, !.

find_smallest_prime_loop(X, Curr, P):-
    NextCurr is Curr + 1,
    find_smallest_prime_loop(X, NextCurr, P).

% X is not a prime number
find_smallest_prime_divisor(X, P):-
    find_smallest_prime_loop(X, 2, P). 

prime_factors(X, [X]):-
    is_prime(X).
prime_factors(X, L):-
    find_smallest_prime_divisor(X, P),
    Rem is X/P,
    prime_factors(Rem, L1),
    append_two_list(L1, [P], L).

% 22. Goldbach's conjecture.
% goldbach(X, L)-> L is a list of two prime numbers whose sum is X
next_prime(P,P1) :- P1 is P + 2, is_prime(P1), !.
next_prime(P,P1) :- P2 is P + 2, next_prime(P2,P1).

goldbach(4,[2,2]).
goldbach(N,L) :-
    N mod 2 =\= 0,
    N > 4,
    goldbach(N,L,3).
goldbach(N,[P,Q],P) :-
    Q is N - P,
    is_prime(Q), P < Q.
goldbach(N,L,P) :-
    P < N,
    next_prime(P,P1),
    goldbach(N,L,P1).

% 23. To count numbers greater than 100.0 in a list.
% num_greater_than_100(L, X) -> X are the number of terms
% in list L that are greater than 100

num_greater_than_100([], 0).

num_greater_than_100([Head| Rest], X):-
    Head > 100, !, 
    num_greater_than_100(Rest, Y),
    X is Y + 1.

num_greater_than_100([_| Rest], X):-
    num_greater_than_100(Rest, X).

% 24. To split a list of numbers in two lists such that 
% one contains negative numbers and other contains positive numbers.
% split(L, X, Y) -> split L into X have +ve and Y havign -ve
split([],[],[]).

split([Head|Tail], [Head|L1], L2):-
    Head >= 0, !,
    split(Tail, L1, L2).

split([Head|Tail], L1, [Head|L2]):-
    split(Tail, L1, L2).