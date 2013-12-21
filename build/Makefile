CXX = color-g++-4.9
CXXFLAGS = -Wall -Wno-deprecated -MMD

VPATH = ../src

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
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o *.d cpm.out

-include $(OBJ_FILES:.o=.d)
