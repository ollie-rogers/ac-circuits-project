# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isource -Iheaders -Iderived_classes

# Source files in 'source' and 'derived_classes'
SRCS = source/main.cpp \
       source/component.cpp \
       source/circuit.cpp \
       source/utils.cpp \
       derived_classes/resistor.cpp \
       derived_classes/inductor.cpp \
       derived_classes/capacitor.cpp

# Object files (auto-replacing .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main.exe

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	del /Q $(OBJS) $(TARGET)  # For Windows CMD (use rm -f if on bash/MINGW)
