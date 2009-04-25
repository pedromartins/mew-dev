add_executable(TestArduino TestArduino.cpp)
target_link_libraries(TestArduino electronic)

add_executable(TestScanning TestScanning.cpp)
target_link_libraries(TestScanning electronic)

add_executable(TestFollowing TestFollowing.cpp)
target_link_libraries(TestFollowing electronic)

add_executable(TestMotors TestMotors.cpp)
target_link_libraries(TestMotors electronic glut)
