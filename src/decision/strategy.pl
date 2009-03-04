/**

mew-robotics

strategy.pl

Provides predicates for the strategy of winning the game.
Includes dispenser/building_area selection predicates, using
heuristics.

@author Hok Shun Poon 
*/


:- ensure_loaded('assembly.pl').

%% exec_strategy
%
% This strategy will cause the robot to build 2 column-high temples and 
% lay them them onto the nearest, highest scoring building area.
%
%
exec_strategy :-
  assemble_temple,  # assemble the temple on the robot.
  select_building_area(X), # find a building area to place the temple.
  put_onto_building_area(X),
  fail.
  


%% select_building_area(X:building_area) is nondet.
%
% Finds the closest, clear, high-scoring building area.
%
select_building_area(X) :-
  update_world_rep(), % updates the world
  !,
  building_area(X),
  building_area_clear(X). % TODO ensure building area is closest, highest scoring.


%% building_area_clear(X)
%
% Holds if the building_area X is clear.
% Returns a clear building_area otherwise.
%
building_area_clear(X):-
  % TODO use CV????

%% build_on(X:building_area)
%
% Pre: Robot is in playing area.
% Post: Robot has built 
%
% Orders the robot to complete the entire 
build_on(ba1_1).
build_on(ba1_2).
  % TODO identify possible positions to place the assembled temple.
  
  
build_on(ba2). % How do you build on ba_2?
build_on(ba3). % How do you build on ba_3?