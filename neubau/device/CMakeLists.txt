add_library(device actuator.cpp sensor.cpp)
target_link_libraries(device electronic)
set_target_properties(device PROPERTIES LINKER_LANGUAGE CXX)
