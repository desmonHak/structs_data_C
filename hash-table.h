#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "debug_c.h"

#if defined(DEBUG_ENABLE) && defined(DEBUG_HASH_TABLE)
#define DEBUG_PRINT_HASH_TABLE DEBUG_PRINT
#else
#define DEBUG_PRINT_HASH_TABLE
#endif

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    size_t size;
    size_t capacity;
    Entry** table;
} HashTable;

HashTable* createHashTable(size_t size);
unsigned long hash(const char* str, size_t size);
void *get(HashTable *hashTable, const char *key);
void put(HashTable *hashTable, const char *key, void *value);
void printHashTable(HashTable *hashTable);
void freeHashTable_struct(HashTable *hashTable);
void freeHashTable_all(HashTable* hashTable, void (*freeValue)(void*));

// Macro para detectar número de argumentos
#define GET_MACRO(_1, _2, NAME, ...) NAME
#ifndef freeHashTable
#define freeHashTable(...) GET_MACRO(__VA_ARGS__, freeHashTable_all, freeHashTable_struct)(__VA_ARGS__)
#endif

#ifdef INCLUDE_COLORS_C
#include "hash-table.c"
#endif
#endif