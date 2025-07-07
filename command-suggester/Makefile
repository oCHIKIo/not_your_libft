# Command Suggester Makefile

# Project info
NAME = command-suggester
VERSION = 1.0.0

# Directories
SRCDIR = src
INCDIR = include
TESTDIR = tests
DATADIR = data
OBJDIR = obj
TESTOBJ = test_obj

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
INCLUDES = -I$(INCDIR)
LIBS = -lm
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Source files
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/similarity.c $(SRCDIR)/database.c $(SRCDIR)/search.c $(SRCDIR)/utils.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Test files
TEST_SOURCES = $(TESTDIR)/test_similarity.c $(TESTDIR)/test_database.c $(TESTDIR)/test_integration.c
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.c=$(TESTOBJ)/%.o)
LIB_SOURCES = $(filter-out $(SRCDIR)/main.c, $(SOURCES))
LIB_OBJECTS = $(LIB_SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default target
all: debug

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

# Release build
release: CFLAGS += $(RELEASE_FLAGS)
release: $(NAME)

# Main executable
$(NAME): $(OBJECTS) | check_data
	$(CC) $(OBJECTS) -o $(NAME) $(LIBS)
	@echo "✓ Built $(NAME) executable"

# Object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Test executables
test_similarity: $(TESTOBJ)/test_similarity.o $(LIB_OBJECTS) | $(TESTOBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test_database: $(TESTOBJ)/test_database.o $(LIB_OBJECTS) | $(TESTOBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

test_integration: $(TESTOBJ)/test_integration.o $(LIB_OBJECTS) | $(TESTOBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Test object files
$(TESTOBJ)/%.o: $(TESTDIR)/%.c | $(TESTOBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create test object directory
$(TESTOBJ):
	mkdir -p $(TESTOBJ)

# Run all tests
test: test_similarity test_database test_integration
	@echo "Running all tests..."
	@echo "================================"
	./test_similarity
	@echo "================================"
	./test_database
	@echo "================================"
	./test_integration
	@echo "================================"
	@echo "✓ All tests completed successfully!"

# Individual test runs
test-similarity: test_similarity
	@echo "Running similarity tests..."
	./test_similarity

test-database: test_database
	@echo "Running database tests..."
	./test_database

test-integration: test_integration
	@echo "Running integration tests..."
	./test_integration

# Check if data files exist
check_data:
	@if [ ! -f $(DATADIR)/commands.txt ]; then \
		echo "Warning: $(DATADIR)/commands.txt not found"; \
		echo "The program will use built-in commands"; \
	fi

# Install (copy to /usr/local/bin)
install: release
	@echo "Installing $(NAME)..."
	sudo cp $(NAME) /usr/local/bin/
	sudo chmod 755 /usr/local/bin/$(NAME)
	@echo "✓ Installed $(NAME) to /usr/local/bin/"

# Uninstall
uninstall:
	@echo "Uninstalling $(NAME)..."
	sudo rm -f /usr/local/bin/$(NAME)
	@echo "✓ Uninstalled $(NAME)"

# Clean build files
clean:
	rm -rf $(OBJDIR) $(TESTOBJ)
	rm -f test_similarity test_database test_integration
	rm -f test_commands.txt test_output.txt
	@echo "✓ Cleaned build files"

# Clean everything including executable
fclean: clean
	rm -f $(NAME)
	@echo "✓ Cleaned everything"

# Rebuild everything
re: fclean all

# Run with sample inputs
demo: $(NAME)
	@echo "=== Command Suggester Demo ==="
	@echo "Testing 'pwdd':"
	./$(NAME) pwdd
	@echo ""
	@echo "Testing 'lss':"
	./$(NAME) lss
	@echo ""
	@echo "Testing 'catt':"
	./$(NAME) catt
	@echo ""
	@echo "Testing 'gerp':"
	./$(NAME) gerp

# Interactive mode
interactive: $(NAME)
	./$(NAME) --interactive

# Benchmark
benchmark: $(NAME)
	./$(NAME) --benchmark

# Algorithm testing
test-algorithms: $(NAME)
	./$(NAME) --test

# Help
help:
	@echo "Available targets:"
	@echo "  all             - Build debug version (default)"
	@echo "  debug           - Build debug version with debug symbols"
	@echo "  release         - Build optimized release version"
	@echo "  test            - Build and run all tests"
	@echo "  test-similarity - Run similarity algorithm tests"
	@echo "  test-database   - Run database tests"
	@echo "  test-integration- Run integration tests"
	@echo "  demo            - Run demonstration with sample inputs"
	@echo "  interactive     - Run in interactive mode"
	@echo "  benchmark       - Run performance benchmarks"
	@echo "  test-algorithms - Test individual algorithms"
	@echo "  install         - Install to /usr/local/bin (requires sudo)"
	@echo "  uninstall       - Remove from /usr/local/bin (requires sudo)"
	@echo "  clean           - Remove object files and test executables"
	@echo "  fclean          - Remove all generated files"
	@echo "  re              - Rebuild everything"
	@echo "  help            - Show this help message"

# Static analysis with clang-static-analyzer (if available)
analyze:
	@if command -v scan-build >/dev/null 2>&1; then \
		echo "Running static analysis..."; \
		scan-build make debug; \
	else \
		echo "scan-build not available, skipping static analysis"; \
	fi

# Memory leak check with valgrind (if available)
memcheck: debug
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running memory leak check..."; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) pwdd; \
	else \
		echo "valgrind not available, skipping memory check"; \
	fi

# Code formatting with clang-format (if available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		echo "Formatting code..."; \
		find $(SRCDIR) $(INCDIR) $(TESTDIR) -name "*.c" -o -name "*.h" | xargs clang-format -i; \
		echo "✓ Code formatted"; \
	else \
		echo "clang-format not available, skipping formatting"; \
	fi

# Documentation generation with doxygen (if available)
docs:
	@if command -v doxygen >/dev/null 2>&1; then \
		echo "Generating documentation..."; \
		doxygen Doxyfile 2>/dev/null || echo "Doxyfile not found, skipping docs"; \
	else \
		echo "doxygen not available, skipping documentation generation"; \
	fi

# Show project statistics
stats:
	@echo "=== Project Statistics ==="
	@echo "Source files: $$(find $(SRCDIR) -name "*.c" | wc -l)"
	@echo "Header files: $$(find $(INCDIR) -name "*.h" | wc -l)"
	@echo "Test files: $$(find $(TESTDIR) -name "*.c" | wc -l)"
	@echo "Total lines of code:"
	@find $(SRCDIR) $(INCDIR) $(TESTDIR) -name "*.c" -o -name "*.h" | xargs wc -l | tail -1
	@echo "Commands in database: $$(grep -E '^[^#].*:.*:' $(DATADIR)/commands.txt 2>/dev/null | wc -l || echo 0)"

.PHONY: all debug release test test-similarity test-database test-integration demo interactive benchmark test-algorithms install uninstall clean fclean re help analyze memcheck format docs stats check_data