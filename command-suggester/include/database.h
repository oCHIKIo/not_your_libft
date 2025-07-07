#ifndef DATABASE_H
#define DATABASE_H

#include <stddef.h>

#define HASH_TABLE_SIZE 1024
#define MAX_COMMAND_LENGTH 256
#define MAX_PACKAGE_LENGTH 256

/* Command entry structure */
typedef struct command_entry {
    char command[MAX_COMMAND_LENGTH];
    char package[MAX_PACKAGE_LENGTH];
    char version[MAX_PACKAGE_LENGTH];
    struct command_entry *next;
} command_entry_t;

/* Hash table for commands */
typedef struct {
    command_entry_t *buckets[HASH_TABLE_SIZE];
    size_t count;
} command_database_t;

/* Hash function */
unsigned int hash_function(const char *str);

/* Database operations */
command_database_t *create_database(void);
void free_database(command_database_t *db);
int add_command(command_database_t *db, const char *command, const char *package, const char *version);
command_entry_t *find_command(command_database_t *db, const char *command);
int load_commands_from_file(command_database_t *db, const char *filename);
void print_database_stats(command_database_t *db);

/* Iterator for database traversal */
typedef struct {
    command_database_t *db;
    size_t bucket_index;
    command_entry_t *current;
} database_iterator_t;

database_iterator_t *create_iterator(command_database_t *db);
command_entry_t *iterator_next(database_iterator_t *iter);
void free_iterator(database_iterator_t *iter);

#endif