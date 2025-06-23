#include "hash-table-dynamic.h"

#include <stdio.h>

void printEntryHashTableDynamic(EntryHashTableDynamic* entry) {
    printf("Entry hash table dynamic:\n");
    printf("entry->table %p\n", entry->table);
    printf("entry->occupancyRate = %f%%\n", entry->occupancyRate);
    printf("entry->table->capacity = %zu\n", entry->table->capacity);
    printf("entry->table->size = %zu\n", entry->table->size);
    printHashTable(entry->table);
    printf("\n\n");
}

int main() {
    // array para almacenar cada key y luego liberarla:
    ArrayList *arr = createArrayList(0, NULL);
    HashTableDynamic *hash_table_dyn = createHashTableDynamic(16);
    for (size_t i = 0; i < 0xff; i++) {
        char *chartter = calloc(2, sizeof(char));
        push_back_a(arr, chartter); // poner el valor en el array
        *chartter = (char)i;
        size_t index_table = put(hash_table_dyn, chartter, "chartter");
        printf("index_table: %zu\n", index_table);
    }
    forEachNew(hash_table_dyn->tables, (void(*)(void *))printEntryHashTableDynamic);

    freeHashTable_struct(hash_table_dyn);
    freeArrayListAndElements(&arr, free); // liberar cada elemento del array

    return 0;
}