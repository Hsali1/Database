CXX = g++
CXXFLAGS =  -std=c++20 -g -Wall
TARGET = TreeDB

# List of object files needed
OBJS = tree.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule for each file
tree.o: tree.cpp tree.h
	$(CXX) $(CXXFLAGS) -c tree.cpp

# Remove
clean:
	rm -f $(OBJS) $(TARGET)