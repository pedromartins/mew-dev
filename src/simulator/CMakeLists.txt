add_subdirectory(samples)

include_directories(include/)

add_library(sim map.c simulator.c)