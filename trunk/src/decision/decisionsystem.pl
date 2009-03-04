/**

mew-robotics

decisionsystem.pl

Entry point of the system (???)

Top-level goal is typically 'win'.


@author Hok Shun Poon 
*/

:- ensure_loaded('strategy.pl'). 
:- ensure_loaded('movement.pl'). # cpp-interface to steering robot.
:- ensure_loaded('assembly.pl'). # temple assembly


% Some identifiers.
building_area(X):-
  building_area_and_height(X,_).

% Heights of the building areas, in millimetres.
building_area_and_height(ba1_1,0).
building_area_and_height(ba1_2,0).
building_area_and_height(ba2, 30).
building_area_and_height(ba3, 60)


% Rules.
%
% The grand strategies are here.


win :- get_most_points.


get_most_points :-
  repeat,         % repeat the same strategy forever.
  exec_strategy,  % 
  fail.
