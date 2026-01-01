# Makefile for WindowsPaint using g++
# Windows GUI application using Win32 API

# Compiler and linker
CXX = g++
WINDRES = windres

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -Iinclude

# Linker flags
LDFLAGS = -mwindows -static-libgcc -static-libstdc++

# Windows libraries
LIBS = -lgdi32 -luser32 -lcomctl32

# Source files
SOURCES = src/main.cpp src/Function.cpp src/Paint.cpp src/Tick.cpp src/WindowsFunction.cpp src/Variable.cpp

# Object files (in build directory)
OBJECTS = $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))

# Resource files (disabled due to encoding issues - can be re-enabled if needed)
# RESOURCES = Project1.rc
# RES_OBJ = $(RESOURCES:.rc=.o)
RES_OBJ =

# Target executable (in build directory)
TARGET = build/WindowsPaint.exe

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJECTS) $(RES_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(RES_OBJ) $(LIBS)
	@echo "Build successful: $(TARGET)"

# Compile source files from src directory to build directory
build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Function.o: src/Function.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Paint.o: src/Paint.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Tick.o: src/Tick.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/WindowsFunction.o: src/WindowsFunction.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Variable.o: src/Variable.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile resource files (disabled)
# %.o: %.rc
# 	$(WINDRES) -i $< -o $@

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
