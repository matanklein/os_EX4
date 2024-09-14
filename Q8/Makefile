# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -pthread

# Target executable
TARGET = board

# Source files
SRCS = main.cpp board.cpp

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking step (compile the target executable)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compilation step (generate object files)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Clean up shared memory objects created during execution
clean-shm:
	@shm_unlink "/board_mem" || true
	@shm_unlink "/mutex_mem" || true

# Run the program in two different terminals (assuming xterm is installed)
run: $(TARGET)
	xterm -hold -e ./$(TARGET) & xterm -hold -e ./$(TARGET)
