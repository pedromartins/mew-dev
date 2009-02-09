# Silly makefile to make compile single source-files as executables
# from the source folder to the bin folder.

CXX=g++
INCLUDE = /usr/include/opencv/
VPATH = src/
BIN = bin/
SRC = src/
CXXFLAGS = -O3 -I$(INCLUDE)
LINKFLAGS = -L"..\..\lib" -lcxcore -lcv -lcvaux -lml -lhighgui -lcvhaartraining

# assumes single .c and .cpp files can compile directly into one
# executable.

OBJECTS_C =   $(notdir $(patsubst %.c, %, $(SOURCE_C)))
OBJECTS_CPP = $(notdir $(patsubst %.cpp, %, $(SOURCE_CPP)))
SOURCE_C = $(wildcard $(SRC)/*.c)
SOURCE_CPP = $(wildcard $(SRC)/*.cpp)

OBJECTS = $(OBJECTS_C) $(OBJECTS_CPP)

# Target for making object files.
%: %.c
	@echo $@
	@$(CXX) $(CXXFLAGS) -o $(addprefix $(BIN),$@) $< $(LINKFLAGS)

# Target for making binaries class.
%: %.cpp
	@echo $@
	@$(CXX) $(CXXFLAGS) -o $(addprefix $(BIN),$@) $< $(LINKFLAGS)

all: $(OBJECTS)

clean: 
	rm *.bin