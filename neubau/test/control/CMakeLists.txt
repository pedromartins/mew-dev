add_executable(TestControl TestControl.cpp)
target_link_libraries(TestControl core control device)
add_test(TestControl TestControl)