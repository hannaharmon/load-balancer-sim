# Makefile for Load Balancer Simulation
# Supports both Windows (MSVC) and Linux/Mac (g++)

# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows with MSVC
    CXX = cl
    CXXFLAGS = /EHsc /W3
    OUTFLAG = /Fe:
    RM = del /Q
    EXE = .exe
    TARGET = loadbalancer.exe
else
    # Linux/Mac with g++
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -Wextra
    OUTFLAG = -o 
    RM = rm -f
    EXE =
    TARGET = loadbalancer
endif

# Source files
SRCS = main.cpp LoadBalancer.cpp Webserver.cpp Request.cpp RequestGenerator.cpp Firewall.cpp Logger.cpp Colors.cpp

# Object files (for non-MSVC builds)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable (MSVC style - single command compilation)
ifeq ($(OS),Windows_NT)
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(OUTFLAG)$(TARGET) $(SRCS)
else
# Unix-style build with object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OUTFLAG)$(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

# Run with default config
run: $(TARGET)
ifeq ($(OS),Windows_NT)
	.\$(TARGET) config.txt
else
	./$(TARGET) config.txt
endif

# Run with specific config
run-config: $(TARGET)
ifeq ($(OS),Windows_NT)
	.\$(TARGET) $(CONFIG)
else
	./$(TARGET) $(CONFIG)
endif

# Clean build artifacts
clean:
ifeq ($(OS),Windows_NT)
	$(RM) *.obj *.exe *.ilk *.pdb 2>nul
else
	$(RM) $(OBJS) $(TARGET) *.o
endif

# Clean everything including logs
clean-all: clean
	$(RM) *.log *.txt

# Run all test configurations
test-all: $(TARGET)
ifeq ($(OS),Windows_NT)
	@echo "Running default configuration..."
	@.\$(TARGET) config.txt
	@echo.
	@echo "Running minimal configuration..."
	@.\$(TARGET) configs\minimal.txt
	@echo.
	@echo "Running high load configuration..."
	@.\$(TARGET) configs\high_load.txt
	@echo.
	@echo "Running firewall test..."
	@.\$(TARGET) configs\firewall_test.txt
else
	@echo "Running default configuration..."
	@./$(TARGET) config.txt
	@echo ""
	@echo "Running minimal configuration..."
	@./$(TARGET) configs/minimal.txt
	@echo ""
	@echo "Running high load configuration..."
	@./$(TARGET) configs/high_load.txt
	@echo ""
	@echo "Running firewall test..."
	@./$(TARGET) configs/firewall_test.txt
endif

# Generate Doxygen documentation (HTML)
docs:
	@echo "Generating Doxygen documentation..."
	doxygen Doxyfile
	@echo "Documentation generated in ./docs/html/"
	@echo "Open ./docs/html/index.html in a browser to view."

# Clean documentation
clean-docs:
ifeq ($(OS),Windows_NT)
	if exist docs rmdir /S /Q docs
else
	$(RM) -r docs
endif

# Help target
help:
	@echo "Load Balancer Makefile"
	@echo "====================="
	@echo "Targets:"
	@echo "  make              - Build the project"
	@echo "  make run          - Build and run with config.txt"
	@echo "  make run-config CONFIG=path/to/config.txt - Run with specific config"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make clean-all    - Remove build artifacts and logs"
	@echo "  make test-all     - Run all test configurations"
	@echo "  make docs         - Generate Doxygen HTML documentation"
	@echo "  make clean-docs   - Remove generated documentation"
	@echo "  make help         - Show this help message"

.PHONY: all run run-config clean clean-all test-all docs clean-docs help
