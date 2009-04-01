include_directories(${NEUBAU_SOURCE_DIR}/device/ ${NEUBAU_SOURCE_DIR}/electronic/ ${NEUBAU_SOURCE_DIR}/control/)
link_directories(${NEUBAU_BINARY_DIR}/electronic)

add_executable(simplecontrol control.cpp)
target_link_libraries(simplecontrol device control)
set_target_properties(simplecontrol PROPERTIES LINKER_LANGUAGE CXX)
