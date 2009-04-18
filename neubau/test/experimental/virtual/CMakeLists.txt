#add_executable(TestVirtualWorld TestVirtualWorld.cpp)
#target_link_libraries(TestVirtualWorld core experimental)
#add_test(TestVirtualWorld TestVirtualWorld)

add_executable(TestVirtual TestVirtual.cpp)
target_link_libraries(TestVirtual core experimental device)
add_test(TestVirtual TestVirtual)