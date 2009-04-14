add_subdirectory(profile)
add_subdirectory(virtual)

add_library(experimental
	profile/simpleprofile.h
	virtual/virtualworld.cpp
	virtual/virtual.h
	)