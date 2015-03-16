Abide by these... OR ELSE!!!!

## Build ##
  * Try to write your own CMakeLists.txt if you create a new directory relevant to the build =]


## File extensions ##
  * .h for C/C++ header files
  * .c for C source files
  * .cpp for C++ source files

## File/Directory names ##
  * File names all lowercase, with words separated by underscore
  * Directory names are all lowercase,
  * Directory structure DOES NOT need to reflect C++ namespace structure.

## C/C++ Source code ##
  * Class names use CamelCase
  * Variable (field) names use mixedCase.
  * public, protected, private identifiers are on the same level as the 'class' keyword
  * no prefixes for members, or global variables, or anything like that. e.g.
```
class LetsHaveABigRoboticsParty {
public:
    /* Everybody has insane fun! */
    virtual void party();

private:
    std::list<Guest> guests;
};
```

  * Indentation is done with tabs only. Tab width may vary, but be consistent =]

  * Constants, macros, and enums are all capital, with underscores separating words. e.g.
```
#define HOW_AMAZING_IS_THIS_CODE 1337

static const int LOL_ON_THE_CEILING = 707;

enum Day {
  MONDAY=1,
  TUESDAY
  // ...
};

```

  * C-style comments for short annotations, // block comments for describing functionality, and writing pre-conditions and post-conditions for class methods, in header files mostly.