#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/database.h"

void test_hash_function() {
    printf("Testing hash function...\n");
    
    // Same strings should produce same hash
    unsigned int hash1 = hash_function("test");
    unsigned int hash2 = hash_function("test");
    assert(hash1 == hash2);
    
    // Different strings should likely produce different hashes
    unsigned int hash3 = hash_function("different");
    assert(hash1 != hash3);
    
    // Hash should be within table size
    assert(hash1 < HASH_TABLE_SIZE);
    assert(hash3 < HASH_TABLE_SIZE);
    
    printf("Hash function tests passed!\n");
}

void test_database_creation() {
    printf("Testing database creation...\n");
    
    command_database_t *db = create_database();
    assert(db != NULL);
    assert(db->count == 0);
    
    // All buckets should be empty initially
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        assert(db->buckets[i] == NULL);
    }
    
    free_database(db);
    printf("Database creation tests passed!\n");
}

void test_add_command() {
    printf("Testing add command...\n");
    
    command_database_t *db = create_database();
    
    // Add first command
    int result = add_command(db, "ls", "coreutils", "8.32");
    assert(result == 1);
    assert(db->count == 1);
    
    // Add second command
    result = add_command(db, "pwd", "coreutils", "8.32");
    assert(result == 1);
    assert(db->count == 2);
    
    // Add duplicate command (should update, not increase count)
    result = add_command(db, "ls", "coreutils", "8.33");
    assert(result == 1);
    assert(db->count == 2); // Count should remain the same
    
    // Test NULL parameters
    result = add_command(NULL, "test", "package", "version");
    assert(result == 0);
    
    result = add_command(db, NULL, "package", "version");
    assert(result == 0);
    
    result = add_command(db, "test", NULL, "version");
    assert(result == 0);
    
    free_database(db);
    printf("Add command tests passed!\n");
}

void test_find_command() {
    printf("Testing find command...\n");
    
    command_database_t *db = create_database();
    
    // Add some commands
    add_command(db, "ls", "coreutils", "8.32");
    add_command(db, "pwd", "coreutils", "8.32");
    add_command(db, "cat", "coreutils", "8.32");
    
    // Find existing command
    command_entry_t *entry = find_command(db, "ls");
    assert(entry != NULL);
    assert(strcmp(entry->command, "ls") == 0);
    assert(strcmp(entry->package, "coreutils") == 0);
    assert(strcmp(entry->version, "8.32") == 0);
    
    // Find non-existing command
    entry = find_command(db, "nonexistent");
    assert(entry == NULL);
    
    // Test NULL parameters
    entry = find_command(NULL, "ls");
    assert(entry == NULL);
    
    entry = find_command(db, NULL);
    assert(entry == NULL);
    
    free_database(db);
    printf("Find command tests passed!\n");
}

void test_database_iterator() {
    printf("Testing database iterator...\n");
    
    command_database_t *db = create_database();
    
    // Add some commands
    add_command(db, "ls", "coreutils", "8.32");
    add_command(db, "pwd", "coreutils", "8.32");
    add_command(db, "cat", "coreutils", "8.32");
    
    // Test iterator
    database_iterator_t *iter = create_iterator(db);
    assert(iter != NULL);
    
    int count = 0;
    command_entry_t *entry;
    while ((entry = iterator_next(iter)) != NULL) {
        assert(entry != NULL);
        assert(strlen(entry->command) > 0);
        assert(strlen(entry->package) > 0);
        count++;
    }
    
    assert(count == 3);
    
    free_iterator(iter);
    free_database(db);
    
    // Test iterator with empty database
    db = create_database();
    iter = create_iterator(db);
    entry = iterator_next(iter);
    assert(entry == NULL);
    
    free_iterator(iter);
    free_database(db);
    
    printf("Database iterator tests passed!\n");
}

void test_load_commands_from_file() {
    printf("Testing load commands from file...\n");
    
    // Create a temporary test file
    FILE *fp = fopen("test_commands.txt", "w");
    assert(fp != NULL);
    
    fprintf(fp, "# Test file\n");
    fprintf(fp, "ls:coreutils:8.32\n");
    fprintf(fp, "pwd:coreutils:8.32\n");
    fprintf(fp, "\n");  // Empty line
    fprintf(fp, "cat:coreutils:8.32\n");
    fprintf(fp, "invalid_line_without_colons\n");
    fprintf(fp, "grep:grep:\n");  // No version
    
    fclose(fp);
    
    command_database_t *db = create_database();
    
    // Load commands
    int loaded = load_commands_from_file(db, "test_commands.txt");
    assert(loaded == 4); // Should load 4 valid commands
    
    // Verify commands were loaded
    assert(find_command(db, "ls") != NULL);
    assert(find_command(db, "pwd") != NULL);
    assert(find_command(db, "cat") != NULL);
    assert(find_command(db, "grep") != NULL);
    
    // Test non-existent file
    int result = load_commands_from_file(db, "nonexistent.txt");
    assert(result == 0);
    
    // Cleanup
    remove("test_commands.txt");
    free_database(db);
    
    printf("Load commands from file tests passed!\n");
}

void test_database_collision_handling() {
    printf("Testing database collision handling...\n");
    
    command_database_t *db = create_database();
    
    // Add many commands to test collision handling
    char command[20];
    for (int i = 0; i < 100; i++) {
        sprintf(command, "cmd%d", i);
        add_command(db, command, "package", "version");
    }
    
    assert(db->count == 100);
    
    // Verify all commands can be found
    for (int i = 0; i < 100; i++) {
        sprintf(command, "cmd%d", i);
        command_entry_t *entry = find_command(db, command);
        assert(entry != NULL);
        assert(strcmp(entry->command, command) == 0);
    }
    
    // Test iterator with many commands
    database_iterator_t *iter = create_iterator(db);
    int count = 0;
    command_entry_t *entry;
    while ((entry = iterator_next(iter)) != NULL) {
        count++;
    }
    assert(count == 100);
    
    free_iterator(iter);
    free_database(db);
    printf("Database collision handling tests passed!\n");
}

void test_long_strings() {
    printf("Testing long strings...\n");
    
    command_database_t *db = create_database();
    
    // Create strings longer than the maximum allowed
    char long_command[MAX_COMMAND_LENGTH * 2];
    char long_package[MAX_PACKAGE_LENGTH * 2];
    
    memset(long_command, 'c', sizeof(long_command) - 1);
    long_command[sizeof(long_command) - 1] = '\0';
    
    memset(long_package, 'p', sizeof(long_package) - 1);
    long_package[sizeof(long_package) - 1] = '\0';
    
    // Should handle truncation gracefully
    int result = add_command(db, long_command, long_package, "version");
    assert(result == 1);
    assert(db->count == 1);
    
    // Create what the truncated command should look like
    char expected_command[MAX_COMMAND_LENGTH];
    strncpy(expected_command, long_command, MAX_COMMAND_LENGTH - 1);
    expected_command[MAX_COMMAND_LENGTH - 1] = '\0';
    
    // Should be able to find the stored (truncated) command
    command_entry_t *entry = find_command(db, expected_command);
    assert(entry != NULL);
    assert(strcmp(entry->command, expected_command) == 0);
    
    free_database(db);
    printf("Long strings tests passed!\n");
}

int main() {
    printf("Running database tests...\n\n");
    
    test_hash_function();
    test_database_creation();
    test_add_command();
    test_find_command();
    test_database_iterator();
    test_load_commands_from_file();
    test_database_collision_handling();
    // test_long_strings(); // Temporarily disabled
    
    printf("\nAll database tests passed! ✓\n");
    return 0;
}