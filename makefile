# Makefile for WindowsPaint using g++
# Windows GUI application using Win32 API

# Compiler and linker
CXX = g++
WINDRES = windres

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinclude

# Linker flags
LDFLAGS = -mwindows -static-libgcc -static-libstdc++

# Windows libraries
LIBS = -lgdi32 -luser32 -lcomctl32

# Source files
SOURCES = src/main.cpp src/Function.cpp src/Paint.cpp src/Tick.cpp src/WindowsFunction.cpp src/Variable.cpp

# Object files (in build directory)
OBJECTS = $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))

# Resource files
RESOURCES = resources/Project1.rc
RES_OBJ = build/Project1.o

# Target executable (in build directory)
TARGET = build/WindowsPaint.exe

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJECTS) $(RES_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(RES_OBJ) $(LIBS)
	@echo "Build successful: $(TARGET)"

# Create build directory if it doesn't exist
build/:
	cmd /c "if not exist build mkdir build"

# Compile source files from src directory to build directory
build/%.o: src/%.cpp | build/
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile resource files
build/Project1.o: resources/Project1.rc | build/
	@echo "Compiling $<"
	@$(WINDRES) -i $< -I include -o $@

# Clean build artifacts
clean:
	del /Q build\*.o build\*.exe 2>nul || true
	@echo "Cleaned build artifacts"

# Rebuild
rebuild: clean all

# Run the application
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
