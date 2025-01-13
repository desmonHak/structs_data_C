#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE
#endif

#include "time_code.h"
#include "hash-table.h"

int main() {

    HashTable* hashTable = createHashTable(100);

    // Insert values
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    put(hashTable, "key1", &value1);
    put(hashTable, "key2", &value2);
    put(hashTable, "key3", &value3);

    for (size_t i = 0; i < 200; i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        unsigned char key[2];
        key[0] = 'A' + i% 'Z'; // Assuming the keys are 'A' to 'J'
        key[1] = '\0';
        //printf_color("%s\n", key);

        put(hashTable, (const char *)key, val);
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "Value for key '%s': %d\n",key, *(unsigned char*)get(hashTable, (const char *)key));
    }

    // Get values
    printf_color("Value for key 'key1': %d\n", *(int*)get(hashTable, (const char *)"key1"));
    printf_color("Value for key 'key2': %d\n", *(int*)get(hashTable, (const char *)"key2"));
    printf_color("Value for key 'key3': %d\n", *(int*)get(hashTable, (const char *)"key3"));

    // Print hash table
    printf_color("Hash Table:\n");
    printHashTable(hashTable);

    // Print size and capacity
    printf_color("Size: %zu\n", hashTable->size);
    printf_color("Capacity: %zu\n", hashTable->capacity);

    // Free memory
    freeHashTable(hashTable);
    puts("memoria liberada");

    return 0;
}
