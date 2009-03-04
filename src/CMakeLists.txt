project(MEWDEV)

include_directories(/usr/include/)
link_directories(/usr/lib/)

add_subdirectory(control)
add_subdirectory(core)
# the decision system is prolog code...
add_subdirectory(device)
add_subdirectory(electronic)
add_subdirectory(experimental)
add_subdirectory(perception)
