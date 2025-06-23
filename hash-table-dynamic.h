#ifndef HASH_TABLE_DYNAMIC_H
#define HASH_TABLE_DYNAMIC_H

#include "array-list.h"
#include "hash-table.h"

/**
 * estructura de datos para tablas de hash "distribuidas"
 */
typedef struct HashTableDynamic {
    /**
     * Array de tablas de hash.
     */
    ArrayList * /*<EntryHashTableDynamic>*/ tables;

    /**
     * tamaño para cada tabla de hash nueva.
     */
    uint32_t size_tables;
} HashTableDynamic;

/**
 * Estructura para las tablas de hash estaticas,
 * almacenara la tabla hash con su "densidad de ocupacion"
 * y la cantidad de entradas ocupadas en esta tabla estatica
 */
typedef struct EntryHashTableDynamic {
    /**
     * Tabla de hash a la que apunta esta entrada
     */
    HashTable *table;       /* 4/8 bytes */

    /**
     * Porcentaje de ocupacion de esta tabla de hash
     */
    float occupancyRate;   /* 4/8 bytes */

    /**
     * cantidad de espacios ocupados en la tabla de hash,
     * el tamaño de la tabla de hash se almacena dentro del puntero
     * "table" en el miembro "capacity"
     */
    //size_t occupiedSlots;   /* 4/8 bytes */

    #if \
        defined(__x86_64__)  || defined(_M_X64)   || \
        defined(__aarch64__) || defined(__ppc64__)
        // si es 64bits la plataforma, se alinea la estructura a 32bytes
        // para intentar alinear a la linea de cache que suele ser de 64 bytes
        size_t padding;     /* 8 bytes */

        // 8 * 4 == 32bytes
    #endif

} EntryHashTableDynamic;

HashTableDynamic* createHashTableDynamic(size_t size_tables);
EntryHashTableDynamic* createEntryHashTableDynamic(HashTable *table);

/**
 * Permite insertar un elemento en una tabla hash estatica especifica
 * @param hashTable tabla hash dinamica
 * @param key clave con la que acceder
 * @param value valor a insertar
 * @param index_hash_table indice de tabla de hash estatica a acceder
 */
static inline void put_dyn_index(
    HashTableDynamic *hashTable, const char *key, void *value, size_t index_hash_table) {
    EntryHashTableDynamic * entry = hashTable->tables->Array[index_hash_table];
    put(entry->table, key, value);
}

/**
 * Permite saber cuantas tablas de hash estaticas existen en la coleccion (tabla
 * de hash dinamica)
 * @param hashTable tabla de hash dinamica de la que averiguar cuantas tablas estaticas existen.
 * @return cantidad de tablas de hash existentes en la coleccion.
 */
static inline size_t get_number_hash_tables_static(HashTableDynamic *hashTable) {
    return hashTable->tables->Size;
}

/**
 * Permite obtener una entrada de la tabla de hash dinamica. Esta entrada
 * tiene una tabla de hash estatica asociada.
 * @param hashTable tabla de hash dinamica de la que obtener una entrada
 * @param index indice de la tabla de hash estatica que obtener
 * @return entrada de la tabla dinamica obtenida.
 */
static inline EntryHashTableDynamic* get_hash_entry_table_by_index(
    HashTableDynamic *hashTable, size_t index) {
    return hashTable->tables->Array[index];
}

void freeEntryHashTableDynamic(EntryHashTableDynamic* entry);

void freeHashTable_dyn_struct(HashTableDynamic *hash_table);

void freeHashTable_dyn_all(HashTableDynamic *hash_table, void (*freeValue)(void*));

#ifdef  freeHashTable_all
#undef  freeHashTable_all
#define freeHashTable_all(hash_table, ...) _Generic((hash_table),       \
    HashTable*: freeHashTable_static_all,                               \
    HashTableDynamic*: freeHashTable_dyn_all,                        \
    default: freeHashTable_static_all)(hash_table,__VA_ARGS__)
#endif


#ifdef   freeHashTable_struct
#undef   freeHashTable_struct
#define  freeHashTable_struct(hash_table) _Generic((hash_table),       \
    HashTable*:     freeHashTable_static_struct,                            \
    HashTableDynamic*: freeHashTable_dyn_struct,                            \
    default: freeHashTable_static_struct)(hash_table)
#endif

#define GET_MACRO(_1, _2, NAME, ...) NAME
#ifndef freeHashTable_dyn
#define freeHashTable_dyn(...) GET_MACRO(__VA_ARGS__, freeHashTable_dyn_all, freeHashTable_dyn_struct)(__VA_ARGS__)
#endif

#ifdef freeHashTable
#define freeHashTable freeHashTable_all
#endif


size_t put_dyn(HashTableDynamic *hashTable, const char *key, void *value);
// sobrecargar put:
#ifdef  put
#undef  put
#define put(hash_table, ...) _Generic((hash_table),     \
    HashTable*: put_static,                             \
    HashTableDynamic*: put_dyn,                         \
    default: put_static)(hash_table,__VA_ARGS__)
#endif


void updateValue_dyn(
    HashTableDynamic* hashTable, size_t index_hash_table, const char* key, void* newValue);
// sobrecarga de updateValue
#ifdef  updateValue
#undef  updateValue
#define updateValue(hash_table, ...) _Generic((hash_table),     \
    HashTable*: updateValue_static,                             \
    HashTableDynamic*: updateValue_dyn,                         \
    default: updateValue_static)(hash_table, __VA_ARGS__);
#endif

void *get_dyn(HashTableDynamic* hashTable, size_t index_hash_table, const char *key);
#ifdef  get
#undef  get
#define get(hash_table, ...) _Generic((hash_table), \
HashTable*: get_static,                             \
HashTableDynamic*: get_dyn,                         \
default: get_static)(hash_table, __VA_ARGS__);
#endif

#endif //HASH_TABLE_DYNAMIC_H
