#ifndef __HASH_TABLE_c__
#define __HASH_TABLE_c__

#include "hash-table.h"
unsigned long hash(register const char* str, register size_t size) {
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(unsigned long, hash)
                TYPE_DATA_DBG(const char*, "str = %s")
                TYPE_DATA_DBG(size_t, "size = %zu")
            END_TYPE_FUNC_DBG,
            str, size);
    #endif
    register size_t hash = 0x1505;

    register int c;
    while ((c = *str++)) { 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c  djb2 hash algorithm */
    }

    return hash % size;
}

HashTable* createHashTable(size_t size) {
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(HashTable*, createHashTable)
                TYPE_DATA_DBG(size_t, "size = %zu")
            END_TYPE_FUNC_DBG,
            size);
    #endif
    HashTable* hashTable; //= (HashTable*)malloc(sizeof(HashTable));
    debug_malloc(HashTable, hashTable, sizeof(HashTable) * 1);

    hashTable->size = 0;
    hashTable->capacity = size;
    //hashTable->table = (Entry**)calloc(size, sizeof(Entry*));
    debug_calloc(Entry*, hashTable->table, size, sizeof(Entry*));
    return hashTable;
}

void put(HashTable* hashTable, const char* key, void* value) {
    if ((key == value) || (key == (const char*)NULL) || (hashTable == NULL)) {
        #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_WARNING,
            INIT_TYPE_FUNC_DBG(void, put)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
                TYPE_DATA_DBG(void*, "value = %p")
            END_TYPE_FUNC_DBG,
            hashTable, key, value);
        #endif
        return;
    }
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void, put)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
                TYPE_DATA_DBG(void*, "value = %p")
            END_TYPE_FUNC_DBG,
            hashTable, key, value);
    #endif

    size_t index = hash(key, hashTable->capacity);
    //printf_color("put: %zu\n", index);

    //Entry* entry = (Entry*)malloc(sizeof(Entry));
    Entry* entry;
    debug_malloc(Entry, entry, sizeof(Entry));

    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = entry;
        hashTable->size++;
    } else {
        Entry* current = hashTable->table[index];
        while (current->next != NULL) {
            if (strcmp(current->key, key) == 0) {
                current->value = value;
                free(entry->key);
                free(entry);
                return;
            }
            current = current->next;
        }
        current->next = entry;
    }

    // Check if table needs to be resized
    if (hashTable->size >= hashTable->capacity) {
        size_t newSize = hashTable->capacity * 2;
        Entry** newTable = (Entry**)calloc(newSize, sizeof(Entry*));

        // Rehash and reinsert existing elements
        for (size_t i = 0; i < hashTable->capacity; i++) {
            Entry* entry = hashTable->table[i];
            while (entry != NULL) {
                Entry* next = entry->next;
                size_t newIndex = hash(entry->key, newSize);
                entry->next = newTable[newIndex];
                newTable[newIndex] = entry;
                entry = next;
            }
        }

        free(hashTable->table);
        hashTable->table = newTable;
        hashTable->capacity = newSize;
    }
}


void* get(HashTable* hashTable, register const char* key) {
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void*, get)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
            END_TYPE_FUNC_DBG,
            hashTable, key);
    #endif
    #ifdef __ERROR_H__ 
    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_WARNING, "get(HashTable* hashTable = %p, const char* key = NULL(%p))\n", hashTable, key);
    }
    #endif

    size_t index = hash(key, hashTable->capacity);

    register Entry* entry = hashTable->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // Key not found
}

void printHashTable(HashTable* hashTable) {

    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void, printHashTable)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            END_TYPE_FUNC_DBG,
            hashTable);

    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO, "printHashTable: NULL(%p)\n", hashTable);
    }
    #endif
    for (size_t i = 0; i < hashTable->capacity; i++) {
        Entry* entry = hashTable->table[i];
        while (entry != NULL) {
            printf_color("Key: %s, Value: %p\n", entry->key, entry->value);
            entry = entry->next;
        }
    }
}
/*
    Función para liberar una HashTable, solo libera las entradas de la tabla de hash y su clave,
    los valores asociados a cada entrada deben ser liberados por el programador.
*/
void freeHashTable_struct(HashTable* hashTable) {
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void, freeHashTable)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            END_TYPE_FUNC_DBG,
            hashTable);

    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT_HASH_TABLE(DEBUG_LEVEL_INFO, "freeHashTable: NULL(%p)\n", hashTable);
    }
    #endif
    for (size_t i = 0; i < hashTable->size; i++) {
        Entry* entry = hashTable->table[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
        hashTable->table[i] = NULL; // Set the table slot to NULL after freeing entries
    }
}

/*
    Función para liberar una HashTable con valores dinámicos usando un callback,
    permite eliminar todos los valores de la tabla hash via callback
*/
void freeHashTable_all(HashTable* hashTable, void (*freeValue)(void*)) {
    if (hashTable == NULL) return;

    for (size_t i = 0; i < hashTable->capacity; i++) {
        Entry* entry = hashTable->table[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            if (freeValue != NULL && temp->value != NULL) {
                freeValue(temp->value);
            }
            free(temp);
        }
    }

    free(hashTable->table);
    free(hashTable);
    printf("HashTable con valores dinámicos liberada.\n");
}

#endif