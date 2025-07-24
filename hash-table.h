/*
 *	Licencia Siumba v1.0 basada en Apache 2.0
 *	
 *	Copyright 2023 Desmon (David)
 *	
 *	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 *	este software y archivos de documentación asociados (el "Software"), para tratar el 
 *	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 *	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 *	Software, y para permitir a las personas a quienes se les proporcione el Software 
 *	hacer lo mismo, sujeto a las siguientes condiciones:
 *	
 *	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 *	copias o partes sustanciales del Software.
 *	
 *	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 *	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 *	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 *	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 *	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 *	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 *	DE ACCIONES EN EL SOFTWARE.
 *	
 *	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 *	titular original de los derechos de autor. Los titulares de derechos de autor 
 *	originales no se responsabilizan de las modificaciones realizadas por terceros.
 *	
 *	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 *	cambios realizados entre versiones, ni revelar porciones específicas de código 
 *	modificado.
 */

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "debug_c.h"


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
static inline unsigned long hash_djb2(register const char* str, register size_t size) {

    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(unsigned long, hash)
            TYPE_DATA_DBG(const char*, "str = %s")
            TYPE_DATA_DBG(size_t, "size = %zu")
        END_TYPE_FUNC_DBG,
        str, size);

    register size_t hash = 0x1505;

    register int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c  djb2 hash algorithm */
    }

    return hash % size;
}
void *get_static(HashTable *hashTable, const char *key);
#ifndef get
#define get(hash_table, ...) _Generic((hash_table), \
HashTable*: get_static,                      \
default: get_static)(hash_table, __VA_ARGS__)
#endif

void* get_static_struct(HashTable* hashTable, void *key, size_t lenght_key);

void put_static_struct(
    HashTable* hashTable, void* key, size_t lenght_key, void* value);

void put_static(HashTable *hashTable, const char *key, void *value);
#ifndef put
#define put(hash_table, ...) _Generic((hash_table), \
    HashTable*: put_static,                      \
    default: put_static)(hash_table, __VA_ARGS__);
#endif

void printHashTable(HashTable *hashTable);
void freeHashTable_static_struct(HashTable *hashTable);
void freeHashTable_static_all(HashTable* hashTable, void (*freeValue)(void*));

void updateValue_static(HashTable* hashTable, const char* key, void* newValue);
#ifndef updateValue
#define updateValue(hash_table, ...) _Generic((hash_table), \
HashTable*: updateValue_static,                      \
default: updateValue_static)(hash_table, __VA_ARGS__);
#endif

/**
 * Permite obtener el tamaño de una tabla de hash estatica en especifico
 * @param hashTable tabla de hash estatica de la que averiguar cuantas entradas
 * fueron ocupadas
 * @return cantidad de entradas ocupadas
 */
static inline size_t get_size_HashTable(HashTable *hashTable) {
    return hashTable->size;
}

/**
 * Permite obtener la capacidad maxima de la tabla de hash estatica
 * @param hashTable tabla de hash de la que averiguar su capacidad
 * @return capacidad de la tabla de hash.
 */
static inline size_t get_capacity_HashTable(HashTable *hashTable) {
    return hashTable->capacity;
}

bool resizeHashTable(HashTable* hashTable, size_t newCapacity);

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length);
unsigned char* base64_decode(const char* data, size_t input_length, size_t* output_length);

// Macro para detectar número de argumentos
#define GET_MACRO(_1, _2, NAME, ...) NAME
#ifndef freeHashTable_static
#define freeHashTable_static(...) GET_MACRO(__VA_ARGS__, freeHashTable_static_all, freeHashTable_static_struct)(__VA_ARGS__)
#endif

#ifndef     freeHashTable_all
#undef      freeHashTable_all
#define     freeHashTable_all(hash_table, ...) _Generic((hash_table),     \
HashTable*: freeHashTable_static_all,                                \
default: freeHashTable_static_all)(hash_table,##__VA_ARGS__)
#endif

#ifndef     freeHashTable_struct
#undef      freeHashTable_struct
#define     freeHashTable_struct(hash_table, ...) _Generic((hash_table),     \
HashTable*: freeHashTable_static_struct,                                \
default: freeHashTable_static_struct)(hash_table,##__VA_ARGS__)
#endif

#ifndef freeHashTable
#define freeHashTable freeHashTable_all
#endif

#ifdef INCLUDE_COLORS_C
#include "hash-table.c"
#endif
#endif