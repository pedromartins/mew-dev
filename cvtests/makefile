CXX=g++
CXXFLAGS = -O3 -I /usr/include/opencv/
LINKFLAGS = -L"..\..\lib" -lcxcore -lcv -lcvaux -lml -lhighgui -lcvhaartraining

SAMPLES_C = $(notdir $(patsubst %.c, %.bin, $(wildcard *.c)))
SAMPLES_CPP = $(notdir $(patsubst %.cpp, %.bin, $(wildcard *.cpp)))

SAMPLES = $(SAMPLES_C) $(SAMPLES_CPP)

all: $(SAMPLES)

run: all
	./test.bin

%.bin: %.c
	@echo $@
	@$(CXX) $(CXXFLAGS) -o $@ $< $(LINKFLAGS)

%.bin: %.cpp
	@echo $@
	@$(CXX) $(CXXFLAGS) -o $@ $< $(LINKFLAGS)

clean: 
	rm *.bin