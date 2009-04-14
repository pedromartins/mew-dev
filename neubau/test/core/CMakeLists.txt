add_executable(TestVector2d TestVector2d.cpp)
target_link_libraries(TestVector2d core)
add_test(TestVector2d TestVector2d)

add_executable(TestAStar TestAStar.cpp)
target_link_libraries(TestAStar core)
add_test(TestAStar TestAStar)