# due to the use of templates, cmake needs to be told that we are using C++.

include_directories(.)
# include_directories(include) # include directory for building core library?

add_library(core core.h)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

