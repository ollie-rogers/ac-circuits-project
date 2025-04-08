# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheaders -Iderived_classes

# Source files in project root and derived_classes
SRCS = main.cpp \
       component.cpp \
       circuit.cpp \
       utils.cpp \
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
