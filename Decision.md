# Introduction #
Decision making is vitally important for the correct operation of the robot.
Imagine that the robot starts in the starting zone. It knows that it's red, and it has no lintels or cylinders loaded.
We pull the cord.

What does the robot do?

Obviously, as humans, we think quite far ahead; a sequence of **goal-prerequisite** links chain up to form a coherent plan in a matter of milliseconds. This reminds me of the old nursery rhyme- "There's a hole in my bucket" .

I shall use Prolog notation to represent the computer's knowledge base about the world.
Imagine the nursery rhyme was a conversation between two Prolog servers (distributed knowledge base. w00t!)

Prolog syntax:
goal(PARAMS):- condition1, condition2, condition3.


---

```
# Eliza:
hashole(X) :- fixhole(X).
fixhole(X) :- bucket(X), get(straw), \+toolong(straw).
toolong(straw) :- cut(straw).
cut(X) :- cutting_tool(Y), get(Y), sharp(Y). # added choice point... for example.

cutting_tool(axe).
cutting_tool(knife).

sharp(X):- cutting_tool(X), \+ tooblunt(X).
sharp(X):- cutting_tool(X), sharpen(X). # implied blunt axe due to failure of first sharp/1 clause.

sharpen(X):- get(stone), makewet(stone).
makewet(X):- get(water).
get(stone). # Henry has no problems getting stones.
get(water):- goto(well), use(bucket).
goto(well). # Henry has no problems getting to the well.
use(X):- bucket(X), \+ hashole(bucket).

# Henry:
bucket(X), hashole(X).
...
toolong(straw).
...
tooblunt(axe).
...
toodry(stone).
```

---


... for you literary enjoyment...
http://en.wikipedia.org/wiki/There%27s_a_Hole_in_My_Bucket

Okay- so Henry never really finished evaluating how to fix his bucket (which is the whole point of the rhyme), but read on, and you'll find out how to avoid these... rather compromising situations =].

# Approaches #
## Hard coding ##
**All** decisions are pre-determined. Branches are expressed directly in the programming language syntax that the software is written. Conditions are checked procedurally, and necessary jumps to the right bits of code are made.
May fail to cover every possible case, and is not very good at reacting to 'unexpected' situations. Code-base will be large and totally unreadable, due to insanely verbose if-then-else statements littered at random nesting levels.

## Decision Tree ##
A decision tree is built at the beginning of the program, but without further 'learning' algorithms, it remains static throughout the execution of the program.
This is functionally identical to hard-coding the decision system, albeit having abstracted out the conditions into objects (Decision Tree nodes) and their associated actions also.

## Rule-based ##
A declarative means of approaching decision making.
Much like in Prolog, in a rule-based system provides a knowledge base, containing facts and rules which reflects accurately on the world. Finding a solution to such decision problems can be done by any tree-search algorithms, such as depth-first (Prolog), breadth-first, and iterative deepening.
The problem with Henry and Eliza was that they used a 'depth-first' search- if the rhyme continued, and Eliza gave the very same answers, then there would be no end, and no decision will ever be arrived at.
However, if we limit the number of times that Henry listens to Eliza (because she's a dumbass anyway), then Henry will backtrack through his options- perhaps he needn't get an axe to cut the straw; what about that perfectly sharp knife over there? His problem would have been solved! That's a 'limited depth-first search'.
This is what makes rule-based decision making different: unlike a declarative approach, back-tracking is implemented to automatically seek for alternative solutions, with a particular chosen algorithm.

## Goal-Oriented Action-Planning ##
A goal is what is something that the entity is trying to prove, or achieve.
Goals may be satisfied only if certain conditions hold.
To evaluate whether a goal holds, simply make the conditions into our new goals (can we achieve this condition?), and try to prove, or achieve, that goal.
Recursion is used to solve this.

### Actions ###
Actions are things that the entity in question can do to manipulate the world in some way. This is directly linked to the 'actuators'. Just what are the bare important
Well, decision structures are required to link-up actions in a sound and complete manner (such that the actions do not conflict with each other) to produce a sound plan.

### Serializing actions to produce a plan ###
Using a decision tree, it is possible to find good plans, dynamically!

A sample **very high level** pseudo-code is shown below.

```
win_game :- get_most_points.

get_most_points :- build_most_temples.
get_most_points :- build_biggest_temples.

build_most_temples :-
  highest_clear_building_area(X), # pick a clear building area 3 or 2 or 1
  build_on(X).

highest_clear_building_area(X):-
  computer_vision_magic(X). # TODO!

build_on(X):-
  holding(cylinder,4),
  building_location(Y,X), # Y is a possible position to build onto X from.
  at(Y), # ensure the robot is at position Y
  building_orientation(Z,Y,X), # Z is an orientation the robot must be at to build at Y onto X.
  align(Z),
  actuate_build,
  ensure_building_complete.

at(Y):-
  movement_magic. # TODO!!

build_biggest_temples:-
  ...

```

You get the point. Pretty powerful. If it fails to get to point Y (with `at(Y)`, for example, the decision-system would automatically backtrack to re-satisfy `building_location(Y,X)`, and pick another building\_location. W00T!


# Design #


# Implementation Details #
I personally really want to use a Prolog-based system.
However, it may just be as effective by implementing a an Iterative Deepening A`*` (IDA`*`) state-search for GOAP for finding a solution.
The difference between the two is that Prolog uses a depth-first search on a decision tree, whereas GOAP requires IDA`*` to operate on a state graph.