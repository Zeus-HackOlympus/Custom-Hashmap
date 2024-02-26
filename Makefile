CXX := g++
CXXFLAGS := -Wall
SRC := $(wildcard ./src/*.cpp)
OBJ := ./build/obj
BIN := ./build/bin
TARGET := encoder
INCLUDE := -I include/
OBJECTS := $(SRC:./src/%.cpp=$(OBJ)/%.o)

.PHONY: all debug clean dirs

all: dirs $(BIN)/$(TARGET)

# $< first dependency
# $@ target

$(BIN)/$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo "execute $(TARGET)"
	@ln -s $@ $(TARGET)

$(OBJ)/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ -MP -MMD

dirs:
	@mkdir -p $(BIN)
	@mkdir -p $(OBJ)

debug: CXXFLAGS += -ggdb
debug: all

clean:
	@echo "removing $(BIN) $(OBJ)"
	@rm -rf $(BIN) $(OBJ)

