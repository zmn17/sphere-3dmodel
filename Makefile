# compiler and flags
CXX = g++
CXXFLAGS = -g -I/usr/include -I/usr/include/GLFW -Iexternal/include
LDFLAGS = -L/usr/lib/ -lGLEW -lglfw -lGL -lm -Lexternal -lopengl_utils

# directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# source and object files
SRCS = $(SRC_DIR)/main.cpp \
	   $(SRC_DIR)/Sphere.cpp 

OBJS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(SRCS)))

# executable name
EXEC = sphere

# default target
all: $(EXEC)

# linking
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# pattern rule for compiling .cpp to .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# run the executable
run: all
	./$(EXEC)

# clean build artifacts
clean:
	rm -f $(BIN_DIR)/*.o $(EXEC)
