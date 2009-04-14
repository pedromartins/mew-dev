add_library(device actuator.cpp sensor.cpp virtualdevices.cpp)
target_link_libraries(device electronic core)
set_target_properties(device PROPERTIES LINKER_LANGUAGE CXX)
