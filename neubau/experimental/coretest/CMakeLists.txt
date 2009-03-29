include_directories(${NEUBAU_SOURCE_DIR}/core)
link_directories(${NEUBAU_BINARY_DIR}/core)

add_executable(VectorPrint VectorPrint.cpp)
target_link_libraries(VectorPrint core)
