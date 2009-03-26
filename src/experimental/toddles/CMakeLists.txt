include_directories(.)

add_executable(toddles mew_i2c.c toddles.cpp)

target_link_libraries(toddles cv highgui)
