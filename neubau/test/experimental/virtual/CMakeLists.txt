add_executable(TestVirtual TestVirtual.cpp)
target_link_libraries(TestVirtual core experimental device)
add_test(TestVirtual TestVirtual)