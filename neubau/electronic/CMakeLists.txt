include_directories(${NEUBAU_SOURCE_DIR}/core/ .)
link_directories(${NEUBAU_BINARY_DIR}/core)

add_library(electronic mew_i2c.c arduino.cpp serial.cpp)
set_target_properties(electronic PROPERTIES LINKER_LANGUAGE CXX)
