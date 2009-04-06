add_library(electronic mew_i2c.cpp arduino.cpp serial.cpp)
set_target_properties(electronic PROPERTIES LINKER_LANGUAGE CXX)
