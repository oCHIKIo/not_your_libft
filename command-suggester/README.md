# Command Suggester

A high-performance fuzzy command suggestion system for Unix-like systems that mimics Ubuntu's "command-not-found" feature. When you type a non-existent command, it suggests similar commands that you might have meant.

## Features

- **Multiple Similarity Algorithms**: Implements 6 different similarity algorithms for accurate suggestions
- **Fast Hash-based Database**: Efficient command lookup and storage using hash tables
- **Ubuntu-compatible Output**: Matches the exact format of Ubuntu's command-not-found
- **Comprehensive Test Suite**: Over 8 test categories ensuring reliability
- **Interactive Mode**: Explore commands interactively
- **Performance Benchmarks**: Built-in performance testing
- **Modular Design**: Clean separation of concerns with well-defined APIs

## Similarity Algorithms

The system uses a hybrid approach combining multiple algorithms:

1. **Levenshtein Distance** - Minimum single-character edits (insertions, deletions, substitutions)
2. **Damerau-Levenshtein Distance** - Includes character transpositions
3. **Jaro-Winkler Similarity** - Gives extra weight to common prefixes
4. **Soundex** - Handles phonetic similarities for pronunciation-based errors
5. **N-gram Similarity** - Compares character sequences (2-gram and 3-gram)
6. **Longest Common Subsequence (LCS)** - Finds shared character patterns

## Installation

### Quick Build

```bash
cd command-suggester
make
```

### System Installation

```bash
make release
sudo make install
```

This installs the `command-suggester` executable to `/usr/local/bin/`.

## Usage

### Basic Usage

```bash
# Suggest similar commands
./command-suggester pwdd
# Output:
# Command 'pwdd' not found, did you mean:
#   command 'pwd' from deb coreutils (8.32-4.1ubuntu1.2)
#   command 'pwdx' from deb procps (2:3.3.17-6ubuntu2.1)
#   command 'pldd' from deb libc-bin (2.35-0ubuntu3.9)
# Try: apt install <deb name>
```

### Command Line Options

```bash
./command-suggester [OPTIONS] COMMAND

Options:
  -h, --help                Show help message
  -v, --version             Show version information
  -V, --verbose             Enable verbose output
  -d, --debug               Enable debug output with similarity scores
  -f, --file FILE           Use custom commands database file
  -i, --interactive         Run in interactive mode
  -b, --benchmark           Run performance benchmarks
  -t, --test                Test similarity algorithms
```

### Interactive Mode

```bash
./command-suggester --interactive
# or
make interactive
```

Interactive mode allows you to test multiple commands without restarting the program:

```
Command Suggester Interactive Mode
Type 'quit' or 'exit' to leave, 'help' for commands.

suggester> pwdd
Command 'pwdd' not found, did you mean:
  command 'pwd' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'pwdx' from deb procps (2:3.3.17-6ubuntu2.1)

suggester> lss
Command 'lss' not found, did you mean:
  command 'ls' from deb coreutils (8.32-4.1ubuntu1.2)

suggester> quit
Goodbye!
```

### Debug Mode

```bash
./command-suggester --debug pwdd
# Shows similarity scores for debugging:
# Suggestions for 'pwdd' (with scores):
#  1. pwd                (0.923) from coreutils
#  2. pwdx               (0.745) from procps
#  3. pldd               (0.698) from libc-bin
```

## Examples

### Common Typos

```bash
# Missing/extra characters
./command-suggester lss     # suggests: ls
./command-suggester pwdd    # suggests: pwd, pwdx, pldd
./command-suggester catt    # suggests: cat

# Transpositions
./command-suggester sl      # suggests: ls
./command-suggester grpe    # suggests: grep

# Phonetic similarities
./command-suggester fined   # suggests: find
./command-suggester gitt    # suggests: git
```

### Custom Database

```bash
# Use custom commands file
./command-suggester -f my_commands.txt unknowncmd

# Custom file format (commands.txt):
# command:package:version
ls:coreutils:8.32-4.1ubuntu1.2
pwd:coreutils:8.32-4.1ubuntu1.2
grep:grep:3.6-1build1
```

## Building and Testing

### Build Targets

```bash
make debug          # Build with debug symbols
make release        # Build optimized version
make test           # Build and run all tests
make demo           # Run demonstration
make clean          # Clean build files
make help           # Show all available targets
```

### Running Tests

```bash
# Run all tests
make test

# Run specific test suites
make test-similarity    # Test similarity algorithms
make test-database      # Test database operations
make test-integration   # Test complete system
```

### Performance Testing

```bash
# Run benchmarks
make benchmark
# or
./command-suggester --benchmark
```

Sample benchmark output:
```
Running benchmarks...
Testing 20 commands...
pwdd       -> 4 suggestions
lss        -> 3 suggestions
catt       -> 2 suggestions

Benchmark Results:
- Total tests: 20
- Time taken: 0.045 seconds
- Average time per search: 2.25 ms
- Average suggestions per command: 3.2
```

## Project Structure

```
command-suggester/
├── src/
│   ├── main.c                    # Main program entry point
│   ├── similarity.c              # Similarity algorithms implementation
│   ├── database.c                # Command database management
│   ├── search.c                  # Fuzzy search engine
│   └── utils.c                   # Utility functions
├── include/
│   ├── similarity.h              # Similarity algorithm declarations
│   ├── database.h                # Database structure definitions
│   ├── search.h                  # Search function declarations
│   └── utils.h                   # Utility function declarations
├── data/
│   ├── commands.txt              # Default command database
│   └── packages.txt              # Package information
├── tests/
│   ├── test_similarity.c         # Similarity algorithm tests
│   ├── test_database.c           # Database operation tests
│   └── test_integration.c        # End-to-end integration tests
├── Makefile                      # Build configuration
└── README.md                     # This documentation
```

## Algorithm Details

### Hybrid Scoring System

The system calculates a weighted similarity score using:

```
score = 0.25 × levenshtein_similarity +
        0.30 × jaro_winkler_similarity +
        0.15 × soundex_similarity +
        0.15 × bigram_similarity +
        0.10 × trigram_similarity +
        0.05 × lcs_similarity
```

Additional bonuses are applied for:
- **Prefix matches**: 20% bonus for commands sharing prefixes
- **Short commands**: 10% bonus for commands ≤ 4 characters

### Performance Characteristics

- **Time Complexity**: O(n × m) per comparison, where n and m are string lengths
- **Space Complexity**: O(k) where k is the database size
- **Hash Table**: O(1) average lookup time
- **Scalability**: Efficiently handles databases with 1000+ commands

## Database Format

The command database uses a simple text format:

```
# Comments start with #
command:package:version

# Examples:
ls:coreutils:8.32-4.1ubuntu1.2
pwd:coreutils:8.32-4.1ubuntu1.2
grep:grep:3.6-1build1
vim:vim:2:8.2.3458-2ubuntu2.2
```

## Memory Management

The system is designed with careful memory management:

- **No memory leaks**: All allocated memory is properly freed
- **Safe allocation**: Custom allocation functions with error checking
- **Efficient storage**: Hash table with linked-list collision resolution
- **Bounded memory**: Maximum limits for command and package name lengths

## Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Ensure all tests pass: `make test`
5. Submit a pull request

### Code Style

- Use 4-space indentation
- Follow K&R style braces
- Add comprehensive comments
- Include error handling
- Write unit tests

## License

This project is open source and available under the MIT License.

## Acknowledgments

- Inspired by Ubuntu's `command-not-found` package
- Similarity algorithms based on established computer science research
- Built as part of the 42 School curriculum extension

---

**Author**: [Your Name]  
**Version**: 1.0.0  
**Last Updated**: 2024