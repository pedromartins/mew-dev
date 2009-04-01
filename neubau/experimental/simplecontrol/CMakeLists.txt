include_directories(${NEUBAU_SOURCE_DIR}/device/ ${NEUBAU_SOURCE_DIR}/electronic/)

add_executable(simplecontrol control.cpp)
target_link_libraries(simplecontrol device)
set_target_properties(simplecontrol PROPERTIES LINKER_LANGUAGE CXX)
