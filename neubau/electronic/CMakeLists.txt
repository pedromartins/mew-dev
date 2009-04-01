
include_directories(${NEUBAU_SOURCE_DIR}/electronic ${NEUBAU_SOURCE_DIR}/core/include)
link_directories(${NEUBAU_BINARY_DIR}/electronic ${NEUBAU_BINARY_DIR}/core)

add_library(electronic)
set_target_properties(electronic PROPERTIES LINKER_LANGUAGE CXX)
