CXX := g++
CXXFLAGS := -Wall
SRC := $(wildcard *.cpp)
TARGET := encoder

.phony: all debug clean

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

debug:
	$(CXX) $(CXXFLAGS) $(SRC) -ggdb -o $(TARGET)

clean:
	-@rm -rf $(TARGET)
