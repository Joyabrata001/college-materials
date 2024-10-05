% reverse_list(L, Res) -> Res is the reversed version of L
reverse_list_acc([], Res, Res).

reverse_list_acc([H|T], Curr, Res):-
    reverse_list_acc(T, [H|Curr], Res).

reverse_list(L, Res):-
    reverse_list_acc(L, [], Res).

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

% min(A, B, C) -> C is the minimum of A and B
min(A, B, B):-
    A >= B, !.

min(A, _, A).


% 1. Monkey Banana Problem.
% There is a monkey at the door into a room. In the middle of the room a banana
% is hanging from the ceiling. The monkey is hungry and wants to get the banana,
% but he cannot stretch high enough from the floor. At the window of the room
% there is a box that the monkey can use. The monkey can perform the following
% actions: walk on the floor, climb the box, push the box around (if he is already
% at it), and grasp the banana if he is standing on the box and directly
% underneath the banana.
% a) Can the monkey grasp the banana?
% b) How can the monkey grasp the banana?

% state( MR, MB , P , B )
% MR -> MOnkey Position at Room (at_door, middle, at_window)
% MB -> Monkey Position wrt Box (on_floor, on_box)
% P -> Box Position (at_door, middle, at_window)
% B -> does the monkey has the banana (has, has_not)


% if box is in middle and monkey is on top of box, monkey can grab the banana
move(
    state(middle, on_box, middle, has_not),
	grasp,
	state(middle, on_box, middle, has)
).


% monkey can climb on top of box
move(
    state(P, on_floor, P, H),
	climb,
	state(P, on_box, P, H)
).


% monkey can push the box from any position P1 to position P2
move(
    state(P1, on_floor, P1, H),
	push(P1, P2),
	state(P2, on_floor, P2, H)
).

% monkey can walk from any position P1 to P2
move(
    state(P1, on_floor, P, H),
	walk(P1, P2),
	state(P2, on_floor, P, H)
).

% monkey can get the banana, if it has the banana
canget(state(_, _, _, has)).

% recursively move from a state to new state and check if the
% monkey has banana or not.
canget(OldState) :-
    move(OldState, _, NewState),
    canget(NewState).

% ?- canget(state(at_door, on_floor, at_window, has_not)).
% true .

% ?- canget(state(at_window, on_floor, at_window, has_not)).
% true .

% 2. Water Jug Problem.
% There are two water jugs with capacities of 4 litres and 3 litres respectively.
% Neither have any measuring markers on them. The water jugs are both initially
% empty. One can fill the water jugs with water completely or partially. One can
% empty completely or partially filled jugs both completely or partially. One can
% transfer the content (water) of one jug (partially or completely} to another jug.
% Write Prolog program that outputs the steps to get exactly 2 litres of water
% in 4 litres jug.
water_jug_print_res([]).
water_jug_print_res([H|L]):-
    print(H), nl,
    water_jug_print_res(L).

% end case (2L in 4L container)
water_jug_recur(2, ThreeL, H):-
    reverse_list([(2, ThreeL)|H], H_rev),
    water_jug_print_res(H_rev).

% fill 4L to max
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    water_jug_recur(4, ThreeL, [(FourL, ThreeL)|H]).

% fill 3L to max
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    water_jug_recur(FourL, 3, [(FourL, ThreeL)|H]).

%empty 4L
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    water_jug_recur(0, ThreeL, [(FourL, ThreeL)|H]).

%empty 3L
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    water_jug_recur(FourL, 0, [(FourL, ThreeL)|H]).

% put 3L content in 4L till 4L is full or 3L is empty
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    JugSum is FourL + ThreeL,
    min(4, JugSum, NewFourL),
    NewThreeL is ThreeL - (NewFourL - FourL),
    water_jug_recur(NewFourL, NewThreeL, [(FourL, ThreeL)|H]).

% put 4L content in 3L till 3L is full or L is empty
water_jug_recur(FourL, ThreeL, H):-
    not(is_member((FourL, ThreeL), H)),
    JugSum is FourL + ThreeL,
    min(3, JugSum, NewThreeL),
    NewFourL is FourL - (NewThreeL - ThreeL),
    water_jug_recur(NewFourL, NewThreeL, [(FourL, ThreeL)|H]).

water_jug():-
    water_jug_recur(0, 0, []).

% ?- water_jug().
% 0,0
% 4,0
% 4,3
% 0,3
% 3,0
% 3,3
% 4,2
% 0,2
% 2,0
% true .

% 3. Missionaries and Cannibals Problem.
% Three missionaries and three cannibals must cross a river using a boat which
% can carry at most two people, under the constraint that, for both banks, if
% there are missionaries present on the bank, they cannot be outnumbered by
% cannibals (if they were, the cannibals would eat the missionaries). The boat
% cannot cross the river by itself with no people on board. Write a Prolog
% program to write the steps to illustrate how can missionaries and cannibals
% can cross the river?

% Boat Position can be left or right (initially left)
mission_canni_print_res([]).
mission_canni_print_res([H|L]):-
    print(H), nl,
    mission_canni_print_res(L).

% success case
mission_canni_recur(0, 0, 3, 3, BoatPosition,H):-
    reverse_list([(0, 0, 3, 3, BoatPosition)|H], H_rev),
    mission_canni_print_res(H_rev).
    
% missionL < CanniL -> Fail
mission_canni_recur(MissionL, CanniL, _, _, _, _):-
    MissionL > 0,
    MissionL < CanniL, !, fail.

% missionR < CanniR -> Fail
mission_canni_recur(_, _, MissionR, CanniR, _, _):-
    MissionR > 0,
    MissionR < CanniR, !, fail.

% boat take two Mission from L to R
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, left, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, left), H)),
    MissionL >= 2,
    NewMissionL is MissionL - 2,
    NewMissionR is MissionR + 2,
    mission_canni_recur(
        NewMissionL, CanniL, NewMissionR, CanniR, right, 
        [(MissionL, CanniL, MissionR, CanniR, left)|H]
    ).

% boat take two Canni from L to R
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, left, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, left), H)),
    CanniL >= 2,
    NewCanniL is CanniL - 2,
    NewCanniR is CanniR + 2,
    mission_canni_recur(
        MissionL, NewCanniL, MissionR, NewCanniR, right, 
        [(MissionL, CanniL, MissionR, CanniR, left)|H]
    ).

% boat take one Canni and one Mission from L to R
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, left, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, left), H)),
    MissionL >= 1,
    CanniL >= 1,
    NewMissionL is MissionL - 1,
    NewCanniL is CanniL - 1,
    NewMissionR is MissionR + 1,
    NewCanniR is CanniR + 1,
    mission_canni_recur(
        NewMissionL, NewCanniL, NewMissionR, NewCanniR, right,
        [(MissionL, CanniL, MissionR, CanniR, left)|H]
    ).

% boat take two Mission from R to L
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, right, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, right), H)),
    MissionR >= 2,
    NewMissionR is MissionR - 2,
    NewMissionL is MissionL + 2,
    mission_canni_recur(
        NewMissionL, CanniL, NewMissionR, CanniR, left, 
        [(MissionL, CanniL, MissionR, CanniR, right)|H]
    ).

% boat take two Canni from R to L
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, right, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, right), H)),
    CanniR >= 2,
    NewCanniR is CanniR - 2,
    NewCanniL is CanniL + 2,
    mission_canni_recur(
        MissionL, NewCanniL, MissionR, NewCanniR, left, 
        [(MissionL, CanniL, MissionR, CanniR, right)|H]
    ).

% boat take one Canni and one Mission from R to L
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, right, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, right), H)),
    MissionR >= 1,
    CanniR >= 1,
    NewMissionR is MissionR - 1,
    NewCanniR is CanniR - 1,
    NewMissionL is MissionL + 1,
    NewCanniL is CanniL + 1,
    mission_canni_recur(
        NewMissionL, NewCanniL, NewMissionR, NewCanniR, left,
        [(MissionL, CanniL, MissionR, CanniR, right)|H]
    ).

% boat take one Mission from L to R
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, left, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, left), H)),
    MissionL >= 1,
    NewMissionL is MissionL - 1,
    NewMissionR is MissionR + 1,
    mission_canni_recur(
        NewMissionL, CanniL, NewMissionR, CanniR, right, 
        [(MissionL, CanniL, MissionR, CanniR, left)|H]
    ).

% boat take one Canni from L to R
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, left, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, left), H)),
    CanniL >= 1,
    NewCanniL is CanniL - 1,
    NewCanniR is CanniR + 1,
    mission_canni_recur(
        MissionL, NewCanniL, MissionR, NewCanniR, right, 
        [(MissionL, CanniL, MissionR, CanniR, left)|H]
    ).

% boat take one Mission from R to L
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, right, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, right), H)),
    MissionR >= 1,
    NewMissionR is MissionR - 1,
    NewMissionL is MissionL + 1,
    mission_canni_recur(
        NewMissionL, CanniL, NewMissionR, CanniR, left, 
        [(MissionL, CanniL, MissionR, CanniR, right)|H]
    ).

% boat take one Canni from R to L
mission_canni_recur(MissionL, CanniL, MissionR, CanniR, right, H):-
    not(is_member((MissionL, CanniL, MissionR, CanniR, right), H)),
    CanniR >= 1,
    NewCanniR is CanniR - 1,
    NewCanniL is CanniL + 1,
    mission_canni_recur(
        MissionL, NewCanniL, MissionR, NewCanniR, left, 
        [(MissionL, CanniL, MissionR, CanniR, right)|H]
    ).

mission_canni():-
    mission_canni_recur(3, 3, 0, 0, left, []).

% ?- mission_canni().
% 3,3,0,0,left
% 3,1,0,2,right
% 3,2,0,1,left
% 3,0,0,3,right
% 3,1,0,2,left
% 1,1,2,2,right
% 2,2,1,1,left
% 0,2,3,1,right
% 0,3,3,0,left
% 0,1,3,2,right
% 1,1,2,2,left
% 0,0,3,3,right
% true .

% 4. Tiger, Goat and Cabbage Problem.
% A farmer is traveling with a tiger, a goat, and a cabbage. We have no idea why
% he would be travelling with such a strange assortment, but there he is anyway.
% At one point in his journey he comes to a river which is too deep to wade
% across, and too wide to swim across so he is in a quandary on how to continue.
% He notices a small boat tied to the near shore, but the boat is too small to fit all
% his belongings into, but it is large enough so that he can safely row across with
% one belonging at a time.
% The problem is that if he rows across with the tiger first, then the goat will eat
% the cabbage, and if he rows across with the cabbage first, the tiger will eat the
% goat.
% How can he safely cross the river with all his things intact? Write a Prolog
% program to illustrate the steps.

tiger_goat_cabbage_print_res([]).
tiger_goat_cabbage_print_res([H|L]):-
    print(H), nl,
    tiger_goat_cabbage_print_res(L).

% tiger_goat_cabbage_recur(TL, GL, CL, TR, GR, CR, BoatPosition, History)
% TL -> Tiger Left -> 0 means not there, 1 means there
% GL -> Goat Left -> 0 means not there, 1 means there
% CL -> Cabbage Left -> 0 means not there, 1 means there
% TL -> Tiger Right -> 0 means not there, 1 means there
% GL -> Goat Right -> 0 means not there, 1 means there
% CL -> Cabbage Right -> 0 means not there, 1 means there
% BoatPosition -> signifies person location wrt river -> left/right

% success case
tiger_goat_cabbage_recur(0, 0, 0, 1, 1, 1, right, H):-
    reverse_list([(0, 0, 0, 1, 1, 1, right)|H], H_rev),
    tiger_goat_cabbage_print_res(H_rev).

% goat eat cabbage -> fail
tiger_goat_cabbage_recur(0, 1, 1, 1, 0, 0, right, _):-
    !, fail.

tiger_goat_cabbage_recur(1, 0, 0, 0, 1, 1, left, _):-
    !, fail.

% tiger eat goat
tiger_goat_cabbage_recur(1, 1, 0, 0, 0, 1, right, _):-
    !, fail.

tiger_goat_cabbage_recur(0, 0, 1, 0, 1, 0, left, _):-
    !, fail.

% row tiger from from L to R
tiger_goat_cabbage_recur(1, GL, CL, 0, GR, CR, left, H):-
    not(is_member((1, GL, CL, 0, GR, CR, left), H)),
    tiger_goat_cabbage_recur(
        0, GL, CL, 1, GR, CR, right, 
        [(1, GL, CL, 0, GR, CR, left)|H]
    ).

% row tiger from R to L
tiger_goat_cabbage_recur(0, GL, CL, 1, GR, CR, right, H):-
    not(is_member((0, GL, CL, 1, GR, CR, right), H)),
    tiger_goat_cabbage_recur(
        1, GL, CL, 0, GR, CR, left, 
        [(0, GL, CL, 1, GR, CR, right)|H]
    ).

% row goat from L to R
tiger_goat_cabbage_recur(TL, 1, CL, TR, 0, CR, left, H):-
    not(is_member((TL, 1, CL, TR, 0, CR, left), H)),
    tiger_goat_cabbage_recur(
        TL, 0, CL, TR, 1, CR, right,
        [(TL, 1, CL, TR, 0, CR, left)|H]
    ).

% row goat from R to L
tiger_goat_cabbage_recur(TL, 0, CL, TR, 1, CR, right, H):-
    not(is_member((TL, 0, CL, TR, 1, CR, right), H)),
    tiger_goat_cabbage_recur(
        TL, 1, CL, TR, 0, CR, left,
        [(TL, 0, CL, TR, 1, CR, right)|H]
    ).

% row cabbage from L to R
tiger_goat_cabbage_recur(TL, GL, 1, TR, GR, 0, left, H):-
    not(is_member((TL, GL, 1, TR, GR, 0, left), H)),
    tiger_goat_cabbage_recur(
        TL, GL, 0, TR, GR, 1, right,
        [(TL, GL, 1, TR, GR, 0, left)|H]
    ).

% row cabbage from R to L
tiger_goat_cabbage_recur(TL, GL, 0, TR, GR, 1, right, H):-
    not(is_member((TL, GL, 0, TR, GR, 1, right), H)),
    tiger_goat_cabbage_recur(
        TL, GL, 1, TR, GR, 0, left,
        [(TL, GL, 0, TR, GR, 1, right)|H]
    ).

% row from L to R without taking anything
tiger_goat_cabbage_recur(TL, GL, CL, TR, GR, CR, left, H):-
    not(is_member((TL, GL, CL, TR, GR, CR, left), H)),
    tiger_goat_cabbage_recur(
        TL, GL, CL, TR, GR, CR, right,
        [(TL, GL, CL, TR, GR, CR, left)|H]
    ).

% row from R to L without taking anything
tiger_goat_cabbage_recur(TL, GL, CL, TR, GR, CR, right, H):-
    not(is_member((TL, GL, CL, TR, GR, CR, right), H)),
    tiger_goat_cabbage_recur(
        TL, GL, CL, TR, GR, CR, left,
        [(TL, GL, CL, TR, GR, CR, right)|H]
    ).

tiger_goat_cabbage():-
    tiger_goat_cabbage_recur(1, 1, 1, 0, 0, 0, left, []).

% ?- tiger_goat_cabbage().
% 1,1,1,0,0,0,left
% 1,0,1,0,1,0,right
% 1,0,1,0,1,0,left
% 0,0,1,1,1,0,right
% 0,1,1,1,0,0,left
% 0,1,0,1,0,1,right
% 0,1,0,1,0,1,left
% 0,0,0,1,1,1,right
% true .
