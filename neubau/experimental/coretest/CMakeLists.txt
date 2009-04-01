include_directories(${NEUBAU_SOURCE_DIR}/core/ ${NEUBAU_SOURCE_DIR}/control/)
link_directories(${NEUBAU_BINARY_DIR}/core ${NEUBAU_BINARY_DIR}/control)

add_executable(VectorPrint VectorPrint.cpp)
target_link_libraries(VectorPrint core control)
