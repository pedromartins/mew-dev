# due to the use of templates, cmake needs to be told that we are using C++.
add_library(core core.h)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
