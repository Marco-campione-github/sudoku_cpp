CXX = clang++
CXXFLAGS = -std=c++17 -g
SOURCES = main.cpp sudoku_board.cpp
TARGET = main

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
