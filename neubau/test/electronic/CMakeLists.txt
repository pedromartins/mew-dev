add_executable(TestArduino TestArduino.cpp)
target_link_libraries(TestArduino electronic)
add_test(TestArduino TestArduino)

add_executable(TestScanning TestScanning.cpp)
target_link_libraries(TestScanning electronic)
add_test(TestScanning TestScanning)

add_executable(TestFollowing TestFollowing.cpp)
target_link_libraries(TestFollowing electronic)
add_test(TestFollowing TestFollowing)

add_executable(TestMotors TestMotors.cpp)
target_link_libraries(TestMotors electronic)
target_link_libraries(TestMotors glut)
add_test(TestMotors TestMotors)
