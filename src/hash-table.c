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

#ifndef __HASH_TABLE_c__
#define __HASH_TABLE_c__

#include "hash-table.h"

/**
 * Permite crear una tabla de hash con un tamaño estatico incialmente,
 * que puede autoredimensionarse segun se necesite.
 * @param size tamaño inicial de la tabla de hash, recomiendo que
 * no sea mas grande de lo que necesite, pero tampoco que sea
 * mas pequeña, debe ser justo lo que necesite ya que la redimension
 * es cara.
 * @return Se devuelve una tabla de hash con la capacidad indicada.
 */
HashTable* createHashTable(size_t size) {

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(HashTable*, createHashTable)
                TYPE_DATA_DBG(size_t, "size = %zu")
            END_TYPE_FUNC_DBG,
            size);

    if (size == 0) {
        return NULL;
    }
    HashTable* hashTable; //= (HashTable*)malloc(sizeof(HashTable));
    debug_calloc(HashTable, hashTable, 1, sizeof(HashTable));

    hashTable->size = 0;
    hashTable->capacity = size;
    hashTable->table = NULL;

    //hashTable->table = (Entry**)calloc(size, sizeof(Entry*));
    debug_calloc(Entry*, hashTable->table, size, sizeof(Entry*));
    if (!hashTable->table) {
        free(hashTable); // Libera la memoria previamente asignada si falla.
        return nullptr;
    }
    return hashTable;
}

/**
 * Permite redimensionar una tabla de hash "estatica" para añadir mas capacidad,
 * se debe tener en cuenta, que al hacer esto, se debera recalcular todos los hash's
 * de la antigua tabla de hash y reinsertar en la nueva.
 * @param hashTable tabla de hash a redimensionar.
 * @param newCapacity nueva capacidad para la tabla de hash "estatica".
 * @return indica si la tabla de hash pudo ser o no redimensionada.
 */
bool resizeHashTable(HashTable* hashTable, size_t newCapacity) {
    if (hashTable == NULL || newCapacity == 0) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "resizeHashTable: Tabla nula o nueva capacidad inválida.\n");
        return false;
    }

    // Crear nueva tabla con la nueva capacidad
    Entry** newTable = (Entry**)calloc(newCapacity, sizeof(Entry*));
    if (newTable == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_ERROR, "resizeHashTable: Error al asignar memoria para la nueva tabla.\n");
        return false;
    }

    // Reinsertar todas las entradas en la nueva tabla
    for (size_t i = 0; i < hashTable->capacity; i++) {
        Entry* entry = hashTable->table[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            size_t newIndex = hash_djb2(entry->key, newCapacity);

            // Insertar al inicio de la nueva lista (preserva chaining)
            entry->next = newTable[newIndex];
            newTable[newIndex] = entry;

            entry = next;
        }
    }

    // Liberar la tabla vieja y actualizar punteros
    free(hashTable->table);
    hashTable->table = newTable;
    hashTable->capacity = newCapacity;

    DEBUG_PRINT(DEBUG_LEVEL_INFO, "resizeHashTable: Tabla redimensionada exitosamente a %zu slots.\n", newCapacity);

    return true;
}


/**
 * Permite meter datos en una tabla de hash "estatica" en realidad, la tabla
 * de hash permite la autoredimension, doblara la capacidad cuando se vea
 * necesario hacerlo.
 * @param hashTable tabla de hash donde ingresar el valor
 * @param key clave que usar para almacenar el valor, la clave sera copiada
 * y se autoliberara la copia al liberar la tabla de hash, las claves orginales,
 * que se pasaron a esta funcion, deberan ser liberadas por el programador
 * si fueron creadas usando memoria dinamica.
 * @param value valor que ingresar, no puede ser el mismo puntero que la clave.
 */
void put_static(HashTable* hashTable, const char* key, void* value) {
    if ((key == value) || (key == (const char*)NULL) || (hashTable == NULL)) {

        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            INIT_TYPE_FUNC_DBG(void, put_static)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
                TYPE_DATA_DBG(void*, "value = %p")
            END_TYPE_FUNC_DBG,
            hashTable, key, value);

        return;
    }

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void, put_static)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
                TYPE_DATA_DBG(const char*, "key = %s")
                TYPE_DATA_DBG(void*, "value = %p")
            END_TYPE_FUNC_DBG,
            hashTable, key, value);

    size_t index = hash_djb2(key, hashTable->capacity);

    Entry* entry = NULL;
    debug_calloc(Entry, entry, 1, sizeof(Entry));

    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;

    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = entry;
        hashTable->size++;
    } else {
        Entry* current = hashTable->table[index];
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                // Clave existente: sobrescribir valor
                current->value = value;
                free(entry->key);
                free(entry);
                return;
            }
            if (current->next == NULL) break;
            current = current->next;
        }
        current->next = entry;
    }

    // Redimensionar si excede la capacidad
    if (hashTable->size >= hashTable->capacity) {
        resizeHashTable(hashTable, hashTable->capacity * 2);
    }
}

/**
 * Permite usar una estructura de datos como clave en una tabla hash.
 * @param hashTable tabla hash en la que introducir los datos
 * @param key estructura de datos o cualquier otro contenido que usar como
 * clave. Para poder hacer esto, los datos recibidos se pasan a base64
 * y se obtiene a posterior su hash.
 * @param lenght_key tamaño de la clave.
 * @param value valor a insertar.
 */
void put_static_struct(
    HashTable* hashTable, void* key, size_t lenght_key, void* value) {

    const char* datos = (char*)key;
    size_t out_len; // tamaño de los datos finales

    // Codificar a base64 los datos recibidos, necesitamos que se han datos imprimibles
    // los datos recibidos, al codificarlo a base64 nos aseguramos de esto y de que acabe
    // en \0
    char* b64 = base64_encode((const unsigned char*)datos, lenght_key, &out_len);


    put_static(hashTable, datos, value);

    // Decodificar
    // size_t decoded_len;
    // unsigned char* decoded = base64_decode(b64, out_len, &decoded_len);
    free(b64); // liberar la clave, ya no es necesaria, se duplico al llamar
    // put_static y se gestionara internamente la copia
}

/**
 * Permite obtener un valor de una tabla de hash, a traves de su clave.
 * @param hashTable tabla de hash de la cual recuperar un valor
 * @param key clave a hashear para obtener el valor.
 * @return valor que se almaceno usando la misma clave.
 */
void* get_static(HashTable* hashTable, register const char* key) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void*, get)
            TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            TYPE_DATA_DBG(const char*, "key = %s")
        END_TYPE_FUNC_DBG,
        hashTable, key);

    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "get(HashTable* hashTable = %p, const char* key = NULL(%p))\n", hashTable, key);
        return NULL;
    }
    if (key == (const char*)NULL) {
        debug_set_level(DEBUG_LEVEL_WARNING);
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "get(HashTable* hashTable = %p, const char* key = NULL(%p))\n", hashTable, key);
        return NULL;
    }

    size_t index = hash_djb2(key, hashTable->capacity);

    register Entry* entry = hashTable->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL; // Key not found
}

/**
 * Permite recuperar un valor usando una estructura o cualquier dato
 * como clave.
 * @param hashTable Tabla de hash de la que recuperar un valor
 * @param key clave que usar para almacenar el dato.
 * @param lenght_key tamaño de la clave a hash'ear
 * @return datos recuperados con la clave
 */
void* get_static_struct(HashTable* hashTable, void *key,
                        size_t lenght_key) {

    const char* datos = (char*)key;
    size_t out_len; // tamaño de los datos finales

    // Codificar a base64 los datos recibidos, necesitamos que se han datos imprimibles
    // los datos recibidos, al codificarlo a base64 nos aseguramos de esto y de que acabe
    // en \0
    char* b64 = base64_encode((const unsigned char*)datos, lenght_key, &out_len);

    void* data = get_static(hashTable, datos);
    free(b64); // liberar la clave, ya no se necesita mas
    return data;
}

/**
 * Permite imprimir la tabla de hash con su valores:
 * @param hashTable tabla de hash que imprimir.
 */
void printHashTable(HashTable* hashTable) {
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void, printHashTable)
                TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            END_TYPE_FUNC_DBG,
            hashTable);

    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "printHashTable: NULL(%p)\n", hashTable);
    }
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
void freeHashTable_static_struct(HashTable* hashTable) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void, freeHashTable_struct)
            TYPE_DATA_DBG(HashTable*, "hashTable = %p")
        END_TYPE_FUNC_DBG,
        hashTable);
    if (hashTable == NULL){
        debug_set_level(DEBUG_LEVEL_INFO);
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "freeHashTable: NULL(%p)\n", hashTable);
        return;
    }
    if (hashTable->table == NULL) return; // If the table is empty, return immediately
    for (size_t i = 0; i < hashTable->capacity; i++) {
        
        Entry* entry = hashTable->table[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
        hashTable->table[i] = NULL; // Set the table slot to NULL after freeing entries
    }
    free(hashTable->table);     // Libera el arreglo de punteros
    hashTable->table = NULL;    // Evitar referencias colgantes
    free(hashTable);            // Libera la estructura principal
    hashTable = NULL;           // Opcional, pero recomendable
}

/*
    Función para liberar una HashTable con valores dinámicos usando un callback,
    permite eliminar todos los valores de la tabla hash via callback
*/
void freeHashTable_static_all(HashTable* hashTable, void (*freeValue)(void*)) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void, freeHashTable_all)
            TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            TYPE_DATA_DBG(void (*)(void*), "freeValue = %p")
        END_TYPE_FUNC_DBG,
        hashTable, freeValue);
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
    hashTable->table = nullptr;    // Evitar referencias colgantes
    free(hashTable);

    DEBUG_PRINT(DEBUG_LEVEL_INFO,"HashTable con valores dinámicos liberada.\n");
}

void updateValue_static(HashTable* hashTable, const char* key, void* newValue) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void, updateValue_static)
            TYPE_DATA_DBG(HashTable*, "hashTable = %p")
            TYPE_DATA_DBG(const char*, "key = %s")
            TYPE_DATA_DBG(void*, "newValue = %p")
        END_TYPE_FUNC_DBG,
        hashTable, key, newValue);

    if (hashTable == NULL || key == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING, "updateValue: Tabla hash o clave nula.\n");
        return;
    }

    size_t index = hash_djb2(key, hashTable->capacity);
    Entry* entry = hashTable->table[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = newValue;
            DEBUG_PRINT(DEBUG_LEVEL_INFO, "Valor actualizado para la clave '%s'.\n", key);
            return;
        }
        entry = entry->next;
    }

    DEBUG_PRINT(DEBUG_LEVEL_WARNING, "updateValue: Clave '%s' no encontrada, no se actualizó ningún valor.\n", key);
}



static inline char base64_lookup(unsigned char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1; // Invalid
}

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length) {
    size_t olen = 4 * ((input_length + 2) / 3);
    char* encoded_data = (char*)malloc(olen + 1);
    if (!encoded_data) return NULL;

    size_t i = 0, j = 0;
    while (i < input_length) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        const char base64_chars[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded_data[j++] = (i > input_length + 1) ? '=' : base64_chars[(triple >> 6) & 0x3F];
        encoded_data[j++] = (i > input_length) ? '=' : base64_chars[triple & 0x3F];
    }

    encoded_data[j] = '\0';
    if (output_length) *output_length = j;
    return encoded_data;
}

unsigned char* base64_decode(const char* data, size_t input_length, size_t* output_length) {
    if (input_length % 4 != 0) return NULL;

    size_t olen = input_length / 4 * 3;
    if (data[input_length - 1] == '=') olen--;
    if (data[input_length - 2] == '=') olen--;

    unsigned char* decoded_data = (unsigned char*)malloc(olen);
    if (!decoded_data) return NULL;

    size_t i = 0, j = 0;
    while (i < input_length) {
        uint32_t sextet_a = base64_lookup(data[i++]);
        uint32_t sextet_b = base64_lookup(data[i++]);
        uint32_t sextet_c = base64_lookup(data[i++]);
        uint32_t sextet_d = base64_lookup(data[i++]);

        if (sextet_a == -1 || sextet_b == -1 || sextet_c == -1 || sextet_d == -1) {
            free(decoded_data);
            return NULL;
        }

        uint32_t triple = (sextet_a << 18) |
                          (sextet_b << 12) |
                          (sextet_c << 6) |
                          sextet_d;

        if (j < olen) decoded_data[j++] = (triple >> 16) & 0xFF;
        if (j < olen) decoded_data[j++] = (triple >> 8) & 0xFF;
        if (j < olen) decoded_data[j++] = triple & 0xFF;
    }

    if (output_length) *output_length = olen;
    return decoded_data;
}

#endif