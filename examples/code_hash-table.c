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

#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE
#endif

#include "time_code.h"
#include "hash-table.h"

int main() {
    typedef struct datos_t {
        int a;
        int b;
    } datos_t;

    datos_t *datos = calloc(1, sizeof(datos));
    *datos = (datos_t){
        .a = 0xbbff,
        .b = 0xffaa
    };

    const char* texto = (char*)datos;
    size_t out_len;

    // Codificar
    char* b64 = base64_encode((const unsigned char*)texto, sizeof(datos_t), &out_len);
    printf("Base64: \"%s\"\n", b64);

    // Decodificar
    size_t decoded_len;
    unsigned char* decoded = base64_decode(b64, out_len, &decoded_len);

    printf("Decodificado: \"%.*s\"\n", (int)decoded_len, decoded);


    HashTable* hashTable = createHashTable(20);
    printf("hashTable->capacity = %zu\n", hashTable->capacity);
    printf("hashTable->size = %zu\n", hashTable->size);

    // Insert values
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    put(hashTable, "key1", &value1);
    put(hashTable, "key2", &value2);
    put(hashTable, "key3", &value3);

    for (size_t i = 0; i < ('Z' - 'A'); i++) {
        int* val = malloc(sizeof(int));
        *val = i;
        unsigned char key[2];
        key[0] = 'A' + (i % ('Z' - 'A')); // Assuming the keys are 'A' to 'J'
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

    // actualizar los valores key1, key2 y key3
    updateValue(hashTable, "key1", NULL);
    updateValue(hashTable, "key2", NULL);
    updateValue(hashTable, "key3", NULL);

    printf("hashTable->capacity = %zu\n", hashTable->capacity);
    printf("hashTable->size = %zu\n", hashTable->size);

    // almacenar una estructura, usando la propia estructura como clave:
    //put_static(hashTable, b64, datos);

    // la clave, no puede ser el mismo puntero que los datos, por eso usaremos una estructura como
    // datos y otra como clave para el ejemplo
    datos_t datos_key = {
        .a = 0xbbff,
        .b = 0xffaa
    };

    put_static_struct(hashTable, &datos_key, sizeof(datos_t), datos);

    printf_color("\n\nHash Table:\n");
    printHashTable(hashTable);

    void *datos_recuperados = get_static_struct(hashTable, &datos_key, sizeof(datos_t));
    printf("datos_recuperados = %p\n", datos_recuperados);





    // Free memory
    freeHashTable(hashTable, free);
    puts("memoria liberada");

    // la clave, debe liberarse, pues "freeHashTable" no libera las claves originales,
    // "put_static" hace una copia de las claves introducidas.
    free(b64);
    free(decoded);


    return 0;
}
