# Note that the Makefile is retained for compatibility,
# if developers wish to continue using plain make.

include_directories(/usr/include/opencv/)

add_executable(contourtest contourtest.cpp)
add_executable(roitest roitest.cpp)

target_link_libraries(contourtest cv highgui)
target_link_libraries(roitest cv highgui)