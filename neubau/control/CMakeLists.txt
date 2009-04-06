# due to the use of templates, cmake needs to be told that we are using C++.
add_library(control steering.cpp)
target_link_libraries(control core)
set_target_properties(control PROPERTIES LINKER_LANGUAGE CXX)
