VPATH = ../src
IDIR = # ../include
LDLIBS = -ldivsufsort

CXX = g++
CXXFLAGS = -Wall -Wno-deprecated -MMD -I$(IDIR)

CPP_FILES := $(wildcard ../src/*.cpp)
OBJ_FILES := $(notdir $(CPP_FILES:.cpp=.o))

.PHONY: all debug release profile clean

all: debug

debug: CXXFLAGS += -g -DDEBUG -O1
debug: cpm.out

release: CXXFLAGS += -O3 -DNDEBUG
release: cpm.out

profile: CXXFLAGS += -O3 -DDEBUG -g
profile: cpm.out

cpm.out: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

clean:
	rm -f *.o *.d cpm.out

-include $(OBJ_FILES:.o=.d)
