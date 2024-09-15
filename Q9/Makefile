# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -pthread

# Executables
SERVER_EXEC = server
CLIENT_EXEC = client

# Source files
SERVER_SRC = server.cpp
CLIENT_SRC = client.cpp

# Object files
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)

# Default target (build both server and client)
all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Rule to build the server executable
$(SERVER_EXEC): $(SERVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXEC) $(SERVER_OBJ)

# Rule to build the client executable
$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_EXEC) $(CLIENT_OBJ)

# Rule to compile server source files into object files
$(SERVER_OBJ): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -c $(SERVER_SRC)

# Rule to compile client source files into object files
$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -c $(CLIENT_SRC)

# Clean up object files and executables
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_EXEC) $(CLIENT_EXEC)

# Run the server
run_server: $(SERVER_EXEC)
	./$(SERVER_EXEC)

# Run the client
run_client: $(CLIENT_EXEC)
	./$(CLIENT_EXEC)

# Phony targets
.PHONY: all clean run_server run_client
