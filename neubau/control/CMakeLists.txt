# due to the use of templates, cmake needs to be told that we are using C++.

add_subdirectory(./include/)
include_directories(./include/ ${NEUBAU_SOURCE_DIR}/core/)

add_library(control steering.cpp)
target_link_libraries(control core)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)
