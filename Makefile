# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source and object files
SRCS = main.cpp component.cpp resistor.cpp utils.cpp inductor.cpp capacitor.cpp circuit.cpp
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = main.exe

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile each .cpp file to .o object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)
