add_executable(contourtest contourtest.cpp)
add_executable(roitest roitest.cpp)

target_link_libraries(contourtest cv highgui)
target_link_libraries(roitest cv highgui)