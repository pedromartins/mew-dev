include_directories(${NEUBAU_SOURCE_DIR}/electronic/ ${NEUBAU_SOURCE_DIR}/core/ .)
link_directories(${NEUBAU_BINARY_DIR}/electronic/ ${NEUBAU_BINARY_DIR}/core)

add_library(device actuator.cpp sensor.cpp)
target_link_libraries(device electronic)
set_target_properties(device PROPERTIES LINKER_LANGUAGE CXX)
