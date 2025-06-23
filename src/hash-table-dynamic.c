#ifndef HASH_TABLE_DYNAMIC_C
#define HASH_TABLE_DYNAMIC_C

#include "hash-table-dynamic.h"

/**
 * Permite crear una tabla de hash dinamica, la estructura como el
 * campo "tables" es necesario liberarlas(ademas los elementos internos
 * del array dinamico).
 *
 * @param size_tables tamaño por defecto para cada tabla de hash nueva.
 * @return tabla de hash dinamica.
 */
HashTableDynamic* createHashTableDynamic(size_t size_tables) {

    HashTableDynamic* table = malloc(sizeof(HashTableDynamic));

    table->size_tables  = size_tables;
    table->tables       = createArrayList(0, NULL);

    return table;
}

/**
 *
 * @param table tabla a asociar con esta entrada.
 * @return entrada a tabla dinamica creada
 */
EntryHashTableDynamic* createEntryHashTableDynamic(HashTable *table) {
    // create estructura de tipo entrada:
    EntryHashTableDynamic* entry = calloc(1,
        sizeof(EntryHashTableDynamic));
    // asociar la tabla
    entry->table = table;
    return entry; // retornar la entrada creada
}

/**
 *
 * @param hashTable Tabla de hash dinamica a la que agregar el valor segun x key dada
 * @param key clave "unica" que usar para correlacionar el valor.
 * @param value valor a almacenar en la tabla de hash
 * @return se retorna el indice te la tabla de hash estatica a la que se ingreso el valor,
 * este identificador es necesario para acceder al valor real ingresado
 */
size_t put_dyn(HashTableDynamic *hashTable, const char *key, void *value) {
    if ((key == value) || (key == NULL) || (hashTable == NULL)) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            INIT_TYPE_FUNC_DBG(void, put_dyn)
                TYPE_DATA_DBG(HashTableDynamic*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
                TYPE_DATA_DBG(void*, "value = %p")
            END_TYPE_FUNC_DBG,
            hashTable, key, value);

        return -1;
    }
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, put_dyn)
                    TYPE_DATA_DBG(HashTableDynamic*, "hashTable = %p")
                    TYPE_DATA_DBG(const char*, "key = %s")
                    TYPE_DATA_DBG(void*, "value = %p")
                END_TYPE_FUNC_DBG,
                hashTable, key, value);

    EntryHashTableDynamic *entry = NULL;

    if (get_number_hash_tables_static(hashTable) == 0) { // si aun no hay entradas
        // insertar a la nueva tabla de hash dinamica, una entrada
        // con una nueva tabla de hash estatica asociada.
        HashTable *static_hash_table = createHashTable(hashTable->size_tables);
        entry = createEntryHashTableDynamic(static_hash_table);
        push_back(hashTable->tables, entry);
    }

    // buscar entrada (tabla de hash) vacia o poco llena
    size_t index_entry = 0;
    for (; index_entry < get_number_hash_tables_static(hashTable); index_entry++) {
        EntryHashTableDynamic* current = get_hash_entry_table_by_index(hashTable, index_entry);

        // si la capacidad de ocupacion de esta entrada/tabla de hash es inferior
        // al 80 %, entonces, obtenerla
        if (current->occupancyRate <= 80.0) {
            entry = current;
            break;
        }
    }

    // todas las entradas están llenas, crear una nueva
    if (entry == NULL) {
        index_entry += 1;
        HashTable *static_hash_table = createHashTable(hashTable->size_tables);
        entry = createEntryHashTableDynamic(static_hash_table);
        push_back(hashTable->tables, entry);
        index_entry = get_size_HashTable(entry->table) - 1;
    }

    // poner en la tabla de hash obtenida, el valor indicado
    put(entry->table, key, value);
    entry->occupancyRate = (
        (float)get_size_HashTable(entry->table) * 100.0f) /
        (float)(get_capacity_HashTable(entry->table)
    );

    return index_entry;
}


/**
 *
 * @param hashTable Tabla de hash dinamica a la que acceder.
 * @param index_hash_table indice de tabla de hash estatica a la que se debe de acceder.
 * @param key clave para acceder a la tabla de hash estatica.
 * @param newValue nuevo valor a poner en la tabla de hash.
 */
void updateValue_dyn(HashTableDynamic* hashTable, size_t index_hash_table, const char* key, void* newValue) {
    char *err = NULL;
    if (hashTable == NULL || hashTable->tables == NULL || hashTable->tables->Size == 0) {
        err = "Error in updateValue_dyn: hashTable == NULL || hashTable->tables->Size == 0\n";
        goto err_exit;
    }
    if (index_hash_table > hashTable->tables->Size) {
        err = "Error in updateValue_dyn: index_hash_table > hashTable->tables->Size\n";
        goto err_exit;
    }

    EntryHashTableDynamic * entry = get_hash_entry_table_by_index(hashTable, index_hash_table);
    updateValue(entry->table, key, newValue);

    return;
    err_exit:
        puts(err);
        exit(-1);
}

void *get_dyn(HashTableDynamic* hashTable, size_t index_hash_table, const char *key) {
    char *err = NULL;
    if (hashTable == NULL || hashTable->tables == NULL || hashTable->tables->Size == 0) {
        err = "Error in get_dyn: hashTable == NULL || hashTable->tables->Size == 0\n";
        goto err_exit;
    }

    EntryHashTableDynamic * entry = get_hash_entry_table_by_index(hashTable, index_hash_table);
    return get(entry->table, key);

    err_exit:
        puts(err);
        exit(-1);
}

/**
 * Permite liberar una entrada de una tabla de hash dinamica
 * @param entry entrada a liberar
 */
void freeEntryHashTableDynamic(EntryHashTableDynamic* entry) {
    freeHashTable_struct(entry->table);
    free(entry);
}

/**
 * Permite liberar la memoria de la tabla de hash dinamica y sus tablas de hash
 * estatica, mas no el contenido almacenado en ellas.
 * @param hash_table tabla de hash dinamica a liberar.
 */
void freeHashTable_dyn_struct(HashTableDynamic *hash_table) {
    freeArrayListAndElements(&hash_table->tables, (void(*)(void *))freeEntryHashTableDynamic);
    free(hash_table);
}

/**
 * Permite liberar la tabla de hash dinamica, sus tablas estaticas internar, y los
 * elementos internos contenido en cada tabla.
 * @param hash_table tabla de hash estatica que liberar
 * @param freeValue funcion que usar para liberar cada elemento interno de las tablas
 * de hash estaticas.
 */
void freeHashTable_dyn_all(HashTableDynamic *hash_table, void (*freeValue)(void*)) {
    for (size_t i = 0; i < hash_table->tables->Size; i++) {
        if (hash_table->tables->Array[i] != NULL){
            EntryHashTableDynamic* entry = get_hash_entry_table_by_index(hash_table, i);
            freeHashTable_all(entry->table, freeValue);
        }
    }
    freeArrayList_struct(&(hash_table->tables));
    free(hash_table);;
}

#endif //HASH_TABLE_DYNAMIC_C
