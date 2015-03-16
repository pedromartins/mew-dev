Nobody likes a broken build.

# Introduction #
A broken build is when the trunk of the project no longer builds, due to the **commit** of incomplete, or erroneous code onto the source tree. Note that local broken builds are (of course!) totally acceptable.

# How to avoid Broken Builds #
Things to remember:
  * Commit ONLY WHEN you know your changes to the tree will not break the build

Good practises:
  * Create empty mock classes with TODO tags. This will allow team members to pick-up on tasks that still need doing, and hopefully increase concurrency.
  * Insert TODO or XXX tags when you must leave the code to do something else.

TODO and XXX tags can be put into code by simply writing it into a comment:
```
int someComplicatedFunction(FantasticLookingBananas flb){
  /// TODO I've yet to implement this function! Returning 0 to ensure compilation.
  return 0;
}
```

# How to fix a Broken Build #
If CMake fails to configure the project:
  * Look at the error generated
  * Identify the offending CMakeLists.txt file
  * Check that any directories, include directories and library-link directories exist
  * Check that any include files and libraries required by the build targets (`add_executable` and `add_library`) can be found
  * If all else fails, omit the offending subdirectory from the build by editing the CMakeLists.txt on the level above (delete `add_subdirectory`, ensure the build is okay again, and commit the changes

If you made changes to the source-code and it doesn't build:
  * Try building the project and identify the offending source files
  * Correct the source files quickly
  * Commit the corrected versions ASAP so that other developers do not update to broken code
  * If that is not possible, start commenting out the offending lines of code, or entire functions and put /**FIXME**/ tags around the place to make sure you will get back to it.