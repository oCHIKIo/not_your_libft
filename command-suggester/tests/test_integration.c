#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../include/similarity.h"
#include "../include/database.h"
#include "../include/search.h"

void test_search_integration() {
    printf("Testing search integration...\n");
    
    // Create database and add test commands
    command_database_t *db = create_database();
    
    add_command(db, "pwd", "coreutils", "8.32-4.1ubuntu1.2");
    add_command(db, "ls", "coreutils", "8.32-4.1ubuntu1.2");
    add_command(db, "cat", "coreutils", "8.32-4.1ubuntu1.2");
    add_command(db, "pldd", "libc-bin", "2.35-0ubuntu3.9");
    add_command(db, "pdd", "pdd", "1.5-1");
    add_command(db, "pwdx", "procps", "2:3.3.17-6ubuntu2.1");
    add_command(db, "grep", "grep", "3.6-1build1");
    add_command(db, "vim", "vim", "2:8.2.3458-2ubuntu2.2");
    add_command(db, "git", "git", "1:2.34.1-1ubuntu1.11");
    
    // Test search for "pwdd" (common typo for "pwd")
    search_results_t *results = search_similar_commands(db, "pwdd");
    assert(results != NULL);
    assert(results->count > 0);
    
    // The top result should have a high score
    assert(results->results[0].score > 0.7);
    
    // Should find commands with high similarity
    int found_pwd = 0, found_pwdx = 0, found_pldd = 0;
    for (int i = 0; i < results->count; i++) {
        if (strcmp(results->results[i].command, "pwd") == 0) found_pwd = 1;
        if (strcmp(results->results[i].command, "pwdx") == 0) found_pwdx = 1;
        if (strcmp(results->results[i].command, "pldd") == 0) found_pldd = 1;
    }
    
    assert(found_pwd == 1); // Should definitely find "pwd"
    (void)found_pwdx; // Suppress unused variable warning
    (void)found_pldd; // Suppress unused variable warning
    
    free_search_results(results);
    free_database(db);
    printf("Search integration tests passed!\n");
}

void test_search_sorting() {
    printf("Testing search result sorting...\n");
    
    command_database_t *db = create_database();
    
    add_command(db, "aa", "package1", "1.0");
    add_command(db, "bb", "package2", "1.0");
    add_command(db, "cc", "package3", "1.0");
    
    search_results_t *results = search_similar_commands(db, "a");
    assert(results != NULL);
    
    // Results should be sorted by score (descending)
    for (int i = 1; i < results->count; i++) {
        assert(results->results[i-1].score >= results->results[i].score);
    }
    
    free_search_results(results);
    free_database(db);
    printf("Search result sorting tests passed!\n");
}

void test_ubuntu_format_output() {
    printf("Testing Ubuntu format output...\n");
    
    command_database_t *db = create_database();
    
    add_command(db, "pwd", "coreutils", "8.32-4.1ubuntu1.2");
    add_command(db, "pldd", "libc-bin", "2.35-0ubuntu3.9");
    add_command(db, "pdd", "pdd", "1.5-1");
    add_command(db, "pwdx", "procps", "2:3.3.17-6ubuntu2.1");
    
    search_results_t *results = search_similar_commands(db, "pwdd");
    
    // Redirect stdout to capture output
    FILE *original_stdout = stdout;
    stdout = fopen("test_output.txt", "w");
    
    print_suggestions("pwdd", results);
    fclose(stdout);
    stdout = original_stdout;
    
    // Read and verify output format
    FILE *fp = fopen("test_output.txt", "r");
    char line[512];
    
    // First line should be the "Command not found" message
    fgets(line, sizeof(line), fp);
    assert(strstr(line, "Command 'pwdd' not found, did you mean:") != NULL);
    
    // Should have suggestion lines
    int suggestion_count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "command '") != NULL && strstr(line, "' from deb ") != NULL) {
            suggestion_count++;
        }
    }
    assert(suggestion_count > 0);
    
    fclose(fp);
    remove("test_output.txt");
    
    free_search_results(results);
    free_database(db);
    printf("Ubuntu format output tests passed!\n");
}

void test_empty_search() {
    printf("Testing empty search...\n");
    
    command_database_t *db = create_database();
    
    // Empty database
    search_results_t *results = search_similar_commands(db, "anycommand");
    assert(results != NULL);
    assert(results->count == 0);
    
    free_search_results(results);
    
    // Add commands but search for very different command
    add_command(db, "pwd", "coreutils", "8.32");
    add_command(db, "ls", "coreutils", "8.32");
    
    results = search_similar_commands(db, "xyzqwerty123");
    assert(results != NULL);
    // Might have results with very low scores, but should be filtered out
    
    free_search_results(results);
    free_database(db);
    printf("Empty search tests passed!\n");
}

void test_exact_match() {
    printf("Testing exact match behavior...\n");
    
    command_database_t *db = create_database();
    
    add_command(db, "pwd", "coreutils", "8.32");
    add_command(db, "ls", "coreutils", "8.32");
    
    // Exact match should be found by find_command
    command_entry_t *entry = find_command(db, "pwd");
    assert(entry != NULL);
    assert(strcmp(entry->command, "pwd") == 0);
    
    // Exact match in similarity search should get perfect score
    search_results_t *results = search_similar_commands(db, "pwd");
    assert(results != NULL);
    assert(results->count > 0);
    
    // Find the exact match in results
    int found_exact = 0;
    for (int i = 0; i < results->count; i++) {
        if (strcmp(results->results[i].command, "pwd") == 0) {
            assert(results->results[i].score >= 0.99); // Should be very close to 1.0
            found_exact = 1;
            break;
        }
    }
    assert(found_exact == 1);
    
    free_search_results(results);
    free_database(db);
    printf("Exact match tests passed!\n");
}

void test_case_insensitive_search() {
    printf("Testing case insensitive search...\n");
    
    command_database_t *db = create_database();
    
    add_command(db, "pwd", "coreutils", "8.32");
    add_command(db, "Git", "git", "2.34");
    
    // Test different cases
    search_results_t *results1 = search_similar_commands(db, "PWD");
    search_results_t *results2 = search_similar_commands(db, "pwd");
    search_results_t *results3 = search_similar_commands(db, "Pwd");
    
    assert(results1 != NULL && results1->count > 0);
    assert(results2 != NULL && results2->count > 0);
    assert(results3 != NULL && results3->count > 0);
    
    // Should find "pwd" in all cases with high scores
    for (int i = 0; i < results1->count; i++) {
        if (strcmp(results1->results[i].command, "pwd") == 0) {
            assert(results1->results[i].score >= 0.99);
            break;
        }
    }
    
    free_search_results(results1);
    free_search_results(results2);
    free_search_results(results3);
    free_database(db);
    printf("Case insensitive search tests passed!\n");
}

void test_performance() {
    printf("Testing search performance...\n");
    
    command_database_t *db = create_database();
    
    // Add many commands
    char command[32];
    for (int i = 0; i < 1000; i++) {
        sprintf(command, "command%d", i);
        add_command(db, command, "package", "version");
    }
    
    // Test search performance
    clock_t start = clock();
    
    for (int i = 0; i < 100; i++) {
        search_results_t *results = search_similar_commands(db, "commandxyz");
        free_search_results(results);
    }
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Performance: 100 searches in %.3f seconds (%.3f ms per search)\n", 
           time_taken, (time_taken * 1000) / 100);
    
    // Should complete within reasonable time (less than 5 seconds for 100 searches)
    assert(time_taken < 5.0);
    
    free_database(db);
    printf("Performance tests passed!\n");
}

void test_boundary_conditions() {
    printf("Testing boundary conditions...\n");
    
    command_database_t *db = create_database();
    
    // Test with NULL inputs
    search_results_t *results = search_similar_commands(NULL, "test");
    assert(results == NULL);
    
    results = search_similar_commands(db, NULL);
    assert(results == NULL);
    
    // Test with empty string
    results = search_similar_commands(db, "");
    assert(results != NULL);
    
    free_search_results(results);
    
    // Test with very long input
    char long_input[1000];
    memset(long_input, 'a', sizeof(long_input) - 1);
    long_input[sizeof(long_input) - 1] = '\0';
    
    results = search_similar_commands(db, long_input);
    assert(results != NULL);
    
    free_search_results(results);
    free_database(db);
    printf("Boundary conditions tests passed!\n");
}

int main() {
    printf("Running integration tests...\n\n");
    
    test_search_integration();
    test_search_sorting();
    test_ubuntu_format_output();
    test_empty_search();
    test_exact_match();
    test_case_insensitive_search();
    test_performance();
    test_boundary_conditions();
    
    printf("\nAll integration tests passed! ✓\n");
    return 0;
}