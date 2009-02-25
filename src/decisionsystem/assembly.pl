/**

mew-robotics

assembly.pl

Provides predicates for the building of a temple.
Uses movement to move to appropriate places.

@author Hok Shun Poon 
*/

:- ensure_loaded('movement.pl').

%% assemble_temple(H:int)
%
% Pre: Robot is in playing area.
% Post: a temple of at least height H <= MAXIMuM HEiGHT will be assembled,
%       robot is in mobile state.
% N.B Height counts the number of cylinders.
% 
% If in any case, the robot has already got 1<=n<=3 cylinders, it will attempt
% to get a cylinder from either the ground, or a dispenser.
%
% Will fail if:
%  - the robot could not find any more playing pieces required by the build.
%
% Ensures that a temple of height H is assembled on the robot,
%
assemble_temple(H):-
  assemble_columns(H),
  assemble_lintel.


%% assemble_columns(H:int)
%
% Pre: Robot is in playing area, Robot can hold more columns.
% Post: two columns, of the same level, will be built.
% 
% Will fail if:
%  - the robot could not find any more cylinders.
% 
assemble_columns(H):-
  


%% assemble_layer
%
% Pre: Robot is in playing area, Robot can hold more cylinders.
% Post: two columns  temple of at least height H <= MAXIMuM HEiGHT will be assembled.
% N.B Height counts the number of cylinders.
% 
% Will fail if:
%  - the robot could not find any cylinders.
%
assemble_layer(H):-
  at_dispenser(X),
  find_cylinder,
  
  
  

%% assemble_layer
%
% Pre: Robot is in playing area, Robot can hold more cylinders.
% Post: two columns  temple of at least height H <= MAXIMuM HEiGHT will be assembled.
% N.B Height counts the number of cylinders.
% 
% Will fail if:
%  - the robot could not find any cylinders.
%


%% pickup_cylinder(P:int)
%
% Pre:  Robot is in playing area. P is bound, P is a valid position
% Post: A new cylinder is placed in the position at P.
%
% Picks up a single cylinder.
% 
% N.B looking from the front of the robot, the position is numbered like so:
%
%       5                         6
%       3                         4
%       1                         2
% | Left claw |             | Right claw |
%
% ... i.e., if P is odd, 
% 
% Will fail if:
%  - the robot could not find any cylinders.
%
pickup_cylinder(P):-
  valid_position(P),
  position_occupied(P),
  

%% pickup_lintel:-
%
% Pre: Robot is in playing area, Robot has space for lintel.
% Post: Lintel is picked up.
% 
% Will fail if:
%  - the robot could not grab a lintel.
%
pickup_lintel:-
  have_space_for_lintel,
  in_front_of_lintel,  
  % TODO.


%% valid_position(P:int)
% 
% A position is valid iff it is a counting number. (+ve non-zero natural number)
valid_position(P):-
  integer(P),
  P>0.
