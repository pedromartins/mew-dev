include_directories(include/)
include_directories(${PROJECT_SOURCE_DIR}/simulator/include/)


add_executable(test test.cpp)

target_link_libraries(test sim)