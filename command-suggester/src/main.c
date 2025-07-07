#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include "similarity.h"
#include "database.h"
#include "search.h"
#include "utils.h"

#define VERSION "1.0.0"
#define DEFAULT_COMMANDS_FILE "data/commands.txt"

/* Global variables */
static int verbose_mode = 0;
static int debug_mode = 0;

/* Function prototypes */
void print_usage(const char *program_name);
void print_version(void);
int run_interactive_mode(command_database_t *db);
int run_benchmark(command_database_t *db);
void test_algorithms(void);

int main(int argc, char *argv[]) {
    const char *commands_file = DEFAULT_COMMANDS_FILE;
    int interactive_mode = 0;
    int benchmark_mode = 0;
    int test_mode = 0;
    
    // Parse command line options
    static struct option long_options[] = {
        {"help",        no_argument,       0, 'h'},
        {"version",     no_argument,       0, 'v'},
        {"verbose",     no_argument,       0, 'V'},
        {"debug",       no_argument,       0, 'd'},
        {"file",        required_argument, 0, 'f'},
        {"interactive", no_argument,       0, 'i'},
        {"benchmark",   no_argument,       0, 'b'},
        {"test",        no_argument,       0, 't'},
        {0, 0, 0, 0}
    };
    
    int c;
    while ((c = getopt_long(argc, argv, "hvVdf:ibt", long_options, NULL)) != -1) {
        switch (c) {
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'v':
                print_version();
                return 0;
            case 'V':
                verbose_mode = 1;
                break;
            case 'd':
                debug_mode = 1;
                break;
            case 'f':
                commands_file = optarg;
                break;
            case 'i':
                interactive_mode = 1;
                break;
            case 'b':
                benchmark_mode = 1;
                break;
            case 't':
                test_mode = 1;
                break;
            case '?':
                fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
                return 1;
            default:
                break;
        }
    }
    
    if (test_mode) {
        test_algorithms();
        return 0;
    }
    
    // Initialize database
    if (verbose_mode) {
        printf("Initializing command database...\n");
    }
    
    command_database_t *db = create_database();
    if (!db) {
        fprintf(stderr, "Error: Failed to create database\n");
        return 1;
    }
    
    // Load commands from file
    if (verbose_mode) {
        printf("Loading commands from %s...\n", commands_file);
    }
    
    if (!file_exists(commands_file)) {
        fprintf(stderr, "Warning: Commands file '%s' not found\n", commands_file);
        fprintf(stderr, "Creating minimal database with common commands...\n");
        
        // Add some common commands manually
        add_command(db, "ls", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "pwd", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "cat", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "grep", "grep", "3.6-1build1");
        add_command(db, "find", "findutils", "4.8.0-1ubuntu3");
        add_command(db, "ps", "procps", "2:3.3.17-6ubuntu2.1");
        add_command(db, "top", "procps", "2:3.3.17-6ubuntu2.1");
        add_command(db, "kill", "procps", "2:3.3.17-6ubuntu2.1");
        add_command(db, "vim", "vim", "2:8.2.3458-2ubuntu2.2");
        add_command(db, "nano", "nano", "6.2-1");
        add_command(db, "git", "git", "1:2.34.1-1ubuntu1.11");
        add_command(db, "make", "make", "4.3-4.1build1");
        add_command(db, "gcc", "gcc", "4:11.2.0-1ubuntu1");
        add_command(db, "ssh", "openssh-client", "1:8.9p1-3ubuntu0.10");
        add_command(db, "curl", "curl", "7.81.0-1ubuntu1.18");
        add_command(db, "wget", "wget", "1.21.2-2ubuntu1");
        add_command(db, "tar", "tar", "1.34+dfsg-1ubuntu0.1.22.04.2");
        add_command(db, "cp", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "mv", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "rm", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "mkdir", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "rmdir", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "touch", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "chmod", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "chown", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "df", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "du", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "head", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "tail", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "sort", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "uniq", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "wc", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "less", "less", "590-1ubuntu0.22.04.3");
        add_command(db, "more", "util-linux", "2.37.2-4ubuntu3.4");
        add_command(db, "man", "man-db", "2.10.2-1");
        add_command(db, "which", "debianutils", "5.7-0.3");
        add_command(db, "whoami", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "date", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "echo", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "printf", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "sed", "sed", "4.8-1ubuntu2");
        add_command(db, "awk", "gawk", "1:5.1.0-1ubuntu0.1");
        add_command(db, "cut", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "paste", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "tr", "coreutils", "8.32-4.1ubuntu1.2");
        add_command(db, "zip", "zip", "3.0-12build2");
        add_command(db, "unzip", "unzip", "6.0-26ubuntu3.2");
        add_command(db, "gzip", "gzip", "1.10-4ubuntu4.1");
        add_command(db, "gunzip", "gzip", "1.10-4ubuntu4.1");
        add_command(db, "ping", "iputils-ping", "3:20211215-1");
        add_command(db, "netstat", "net-tools", "1.60+git20181103.0eebece-1ubuntu5");
        add_command(db, "ifconfig", "net-tools", "1.60+git20181103.0eebece-1ubuntu5");
        add_command(db, "mount", "util-linux", "2.37.2-4ubuntu3.4");
        add_command(db, "umount", "util-linux", "2.37.2-4ubuntu3.4");
        add_command(db, "fdisk", "util-linux", "2.37.2-4ubuntu3.4");
        add_command(db, "free", "procps", "2:3.3.17-6ubuntu2.1");
        add_command(db, "uptime", "procps", "2:3.3.17-6ubuntu2.1");
        add_command(db, "htop", "htop", "3.0.5-7build2");
        
        // Some common typos for testing
        add_command(db, "pldd", "libc-bin", "2.35-0ubuntu3.9");
        add_command(db, "pdd", "pdd", "1.5-1");
        add_command(db, "pwdx", "procps", "2:3.3.17-6ubuntu2.1");
        
    } else {
        int loaded = load_commands_from_file(db, commands_file);
        if (loaded == 0) {
            fprintf(stderr, "Warning: No commands loaded from file\n");
        } else if (verbose_mode) {
            printf("Loaded %d commands\n", loaded);
        }
    }
    
    if (verbose_mode || debug_mode) {
        print_database_stats(db);
        printf("\n");
    }
    
    if (benchmark_mode) {
        return run_benchmark(db);
    }
    
    if (interactive_mode) {
        return run_interactive_mode(db);
    }
    
    // Command-line mode
    if (optind >= argc) {
        fprintf(stderr, "Error: No command specified\n");
        fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
        free_database(db);
        return 1;
    }
    
    const char *input_command = argv[optind];
    
    // Check if command exists in database
    command_entry_t *exact_match = find_command(db, input_command);
    if (exact_match) {
        if (verbose_mode) {
            printf("Command '%s' exists in package %s\n", 
                   input_command, exact_match->package);
        }
        free_database(db);
        return 0;
    }
    
    // Search for similar commands
    search_results_t *results = search_similar_commands(db, input_command);
    
    if (debug_mode) {
        print_detailed_results(input_command, results);
    } else {
        print_suggestions(input_command, results);
    }
    
    // Cleanup
    free_search_results(results);
    free_database(db);
    
    return 0;
}

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] COMMAND\n", program_name);
    printf("       %s [OPTIONS] --interactive\n", program_name);
    printf("\n");
    printf("Command suggestion system that mimics Ubuntu's command-not-found.\n");
    printf("\n");
    printf("OPTIONS:\n");
    printf("  -h, --help                Show this help message\n");
    printf("  -v, --version             Show version information\n");
    printf("  -V, --verbose             Enable verbose output\n");
    printf("  -d, --debug               Enable debug output with scores\n");
    printf("  -f, --file FILE           Use FILE as commands database\n");
    printf("  -i, --interactive         Run in interactive mode\n");
    printf("  -b, --benchmark           Run benchmarks\n");
    printf("  -t, --test                Test similarity algorithms\n");
    printf("\n");
    printf("EXAMPLES:\n");
    printf("  %s pwdd                   # Suggest similar commands to 'pwdd'\n", program_name);
    printf("  %s -f data/commands.txt ls # Use custom database\n", program_name);
    printf("  %s --interactive          # Interactive mode\n", program_name);
    printf("  %s --debug pwdd           # Show scores for debugging\n", program_name);
    printf("\n");
}

void print_version(void) {
    printf("Command Suggester %s\n", VERSION);
    printf("A fuzzy command suggestion system for Unix-like systems.\n");
}

int run_interactive_mode(command_database_t *db) {
    printf("Command Suggester Interactive Mode\n");
    printf("Type 'quit' or 'exit' to leave, 'help' for commands.\n\n");
    
    char input[256];
    
    while (1) {
        printf("suggester> ");
        fflush(stdout);
        
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = '\0';
        str_trim(input);
        
        if (str_isempty(input)) {
            continue;
        }
        
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
            break;
        }
        
        if (strcmp(input, "help") == 0) {
            printf("Available commands:\n");
            printf("  help     - Show this help\n");
            printf("  stats    - Show database statistics\n");
            printf("  quit     - Exit interactive mode\n");
            printf("  <cmd>    - Search for similar commands\n");
            continue;
        }
        
        if (strcmp(input, "stats") == 0) {
            print_database_stats(db);
            continue;
        }
        
        // Search for command
        command_entry_t *exact_match = find_command(db, input);
        if (exact_match) {
            printf("Command '%s' exists in package %s\n", 
                   input, exact_match->package);
            continue;
        }
        
        search_results_t *results = search_similar_commands(db, input);
        
        if (debug_mode) {
            print_detailed_results(input, results);
        } else {
            print_suggestions(input, results);
        }
        
        free_search_results(results);
        printf("\n");
    }
    
    printf("Goodbye!\n");
    return 0;
}

int run_benchmark(command_database_t *db) {
    printf("Running benchmarks...\n\n");
    
    const char *test_commands[] = {
        "pwdd", "lss", "catt", "gerp", "findd", "pss", "vimm", 
        "gittt", "makee", "gccc", "sssh", "curll", "wgett",
        "taar", "ccp", "mvv", "rmm", "mkdirr", "touchh"
    };
    const int num_tests = sizeof(test_commands) / sizeof(test_commands[0]);
    
    printf("Testing %d commands...\n", num_tests);
    
    clock_t start = clock();
    int total_suggestions = 0;
    
    for (int i = 0; i < num_tests; i++) {
        search_results_t *results = search_similar_commands(db, test_commands[i]);
        total_suggestions += results->count;
        
        printf("%-10s -> %d suggestions\n", test_commands[i], results->count);
        
        free_search_results(results);
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nBenchmark Results:\n");
    printf("- Total tests: %d\n", num_tests);
    printf("- Total suggestions: %d\n", total_suggestions);
    printf("- Time taken: %.3f seconds\n", time_taken);
    printf("- Average time per search: %.3f ms\n", (time_taken * 1000) / num_tests);
    printf("- Average suggestions per command: %.1f\n", (double)total_suggestions / num_tests);
    
    return 0;
}

void test_algorithms(void) {
    printf("Testing similarity algorithms...\n\n");
    
    const char *test_pairs[][2] = {
        {"pwd", "pwdd"},
        {"ls", "lss"},
        {"cat", "catt"},
        {"grep", "gerp"},
        {"find", "findd"},
        {"vim", "vimm"},
        {"git", "gitt"},
        {"make", "makee"},
        {"hello", "helo"},
        {"world", "word"}
    };
    const int num_pairs = sizeof(test_pairs) / sizeof(test_pairs[0]);
    
    printf("%-15s %-15s %s %s %s %s %s %s\n", 
           "String1", "String2", "Lev", "D-Lev", "J-W", "Sound", "2-gram", "LCS");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_pairs; i++) {
        const char *s1 = test_pairs[i][0];
        const char *s2 = test_pairs[i][1];
        
        int lev = levenshtein_distance(s1, s2);
        int dlev = damerau_levenshtein_distance(s1, s2);
        double jw = jaro_winkler_similarity(s1, s2);
        int soundex_match = soundex_similarity(s1, s2);
        double ngram2 = ngram_similarity(s1, s2, 2);
        double lcs_sim = lcs_similarity(s1, s2);
        
        printf("%-15s %-15s %3d %5d %5.3f %5s %6.3f %5.3f\n", 
               s1, s2, lev, dlev, jw, soundex_match ? "Yes" : "No", ngram2, lcs_sim);
    }
    
    printf("\nSoundex codes:\n");
    for (int i = 0; i < num_pairs; i++) {
        char code1[5], code2[5];
        soundex(test_pairs[i][0], code1);
        soundex(test_pairs[i][1], code2);
        printf("%-15s -> %s\n", test_pairs[i][0], code1);
        printf("%-15s -> %s\n", test_pairs[i][1], code2);
        printf("\n");
    }
}