#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "utils.h"

/* Hash function - djb2 algorithm */
unsigned int hash_function(const char *str) {
    unsigned int hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    return hash % HASH_TABLE_SIZE;
}

/* Create a new database */
command_database_t *create_database(void) {
    command_database_t *db = safe_malloc(sizeof(command_database_t));
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        db->buckets[i] = NULL;
    }
    db->count = 0;
    
    return db;
}

/* Free database and all entries */
void free_database(command_database_t *db) {
    if (!db) return;
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        command_entry_t *current = db->buckets[i];
        while (current) {
            command_entry_t *next = current->next;
            free(current);
            current = next;
        }
    }
    
    free(db);
}

/* Add a command to the database */
int add_command(command_database_t *db, const char *command, const char *package, const char *version) {
    if (!db || !command || !package) return 0;
    
    unsigned int hash = hash_function(command);
    
    // Check if command already exists
    command_entry_t *current = db->buckets[hash];
    while (current) {
        if (strcmp(current->command, command) == 0) {
            // Update existing entry
            strncpy(current->package, package, MAX_PACKAGE_LENGTH - 1);
            current->package[MAX_PACKAGE_LENGTH - 1] = '\0';
            if (version) {
                strncpy(current->version, version, MAX_PACKAGE_LENGTH - 1);
                current->version[MAX_PACKAGE_LENGTH - 1] = '\0';
            }
            return 1;
        }
        current = current->next;
    }
    
    // Create new entry
    command_entry_t *new_entry = safe_malloc(sizeof(command_entry_t));
    
    strncpy(new_entry->command, command, MAX_COMMAND_LENGTH - 1);
    new_entry->command[MAX_COMMAND_LENGTH - 1] = '\0';
    
    strncpy(new_entry->package, package, MAX_PACKAGE_LENGTH - 1);
    new_entry->package[MAX_PACKAGE_LENGTH - 1] = '\0';
    
    if (version) {
        strncpy(new_entry->version, version, MAX_PACKAGE_LENGTH - 1);
        new_entry->version[MAX_PACKAGE_LENGTH - 1] = '\0';
    } else {
        new_entry->version[0] = '\0';
    }
    
    // Insert at beginning of bucket
    new_entry->next = db->buckets[hash];
    db->buckets[hash] = new_entry;
    db->count++;
    
    return 1;
}

/* Find a command in the database */
command_entry_t *find_command(command_database_t *db, const char *command) {
    if (!db || !command) return NULL;
    
    unsigned int hash = hash_function(command);
    command_entry_t *current = db->buckets[hash];
    
    while (current) {
        if (strcmp(current->command, command) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/* Load commands from file */
int load_commands_from_file(command_database_t *db, const char *filename) {
    if (!db || !filename) return 0;
    
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 0;
    }
    
    char line[1024];
    int loaded = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines and comments
        if (strlen(line) == 0 || line[0] == '#') continue;
        
        // Parse line format: command:package:version
        char *command = strtok(line, ":");
        char *package = strtok(NULL, ":");
        char *version = strtok(NULL, ":");
        
        if (command && package) {
            str_trim(command);
            str_trim(package);
            if (version) str_trim(version);
            
            if (add_command(db, command, package, version)) {
                loaded++;
            }
        }
    }
    
    fclose(fp);
    debug_print("Loaded %d commands from %s", loaded, filename);
    return loaded;
}

/* Print database statistics */
void print_database_stats(command_database_t *db) {
    if (!db) return;
    
    printf("Database Statistics:\n");
    printf("- Total commands: %zu\n", db->count);
    
    // Calculate load factor and distribution
    int used_buckets = 0;
    int max_chain = 0;
    int total_chain_length = 0;
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (db->buckets[i]) {
            used_buckets++;
            int chain_length = 0;
            command_entry_t *current = db->buckets[i];
            while (current) {
                chain_length++;
                current = current->next;
            }
            if (chain_length > max_chain) max_chain = chain_length;
            total_chain_length += chain_length;
        }
    }
    
    printf("- Used buckets: %d/%d (%.1f%%)\n", 
           used_buckets, HASH_TABLE_SIZE, 
           (100.0 * used_buckets) / HASH_TABLE_SIZE);
    printf("- Average chain length: %.2f\n", 
           used_buckets > 0 ? (double)total_chain_length / used_buckets : 0.0);
    printf("- Maximum chain length: %d\n", max_chain);
    printf("- Load factor: %.3f\n", (double)db->count / HASH_TABLE_SIZE);
}

/* Iterator implementation */
database_iterator_t *create_iterator(command_database_t *db) {
    if (!db) return NULL;
    
    database_iterator_t *iter = safe_malloc(sizeof(database_iterator_t));
    iter->db = db;
    iter->bucket_index = 0;
    iter->current = NULL;
    
    // Find first non-empty bucket
    while (iter->bucket_index < HASH_TABLE_SIZE && !db->buckets[iter->bucket_index]) {
        iter->bucket_index++;
    }
    
    if (iter->bucket_index < HASH_TABLE_SIZE) {
        iter->current = db->buckets[iter->bucket_index];
    }
    
    return iter;
}

command_entry_t *iterator_next(database_iterator_t *iter) {
    if (!iter || !iter->current) return NULL;
    
    command_entry_t *result = iter->current;
    
    // Move to next entry
    iter->current = iter->current->next;
    
    // If no more entries in current bucket, find next non-empty bucket
    if (!iter->current) {
        iter->bucket_index++;
        while (iter->bucket_index < HASH_TABLE_SIZE && !iter->db->buckets[iter->bucket_index]) {
            iter->bucket_index++;
        }
        
        if (iter->bucket_index < HASH_TABLE_SIZE) {
            iter->current = iter->db->buckets[iter->bucket_index];
        }
    }
    
    return result;
}

void free_iterator(database_iterator_t *iter) {
    if (iter) {
        free(iter);
    }
}