# hash-table.h

----

Esta implementacion de tablas de hash hace uso del algoritmo de hashing `hash djb2`, un algoritmo relativamente eficiente y de baja colision comunmente usado para este tipo de implementaciones.

Las funciones con las que contamos son las siguientes:
```C
HashTable* createHashTable(size_t size);
static inline unsigned long hash_djb2(register const char* str, register size_t size);

void *get_static(HashTable *hashTable, const char *key);
void *get_static_struct(HashTable* hashTable, void *key, size_t lenght_key);

void put_static(HashTable *hashTable, const char *key, void *value);
void put_static_struct(HashTable* hashTable, void* key, size_t lenght_key, void* value);

void printHashTable(HashTable *hashTable);
void freeHashTable_static_struct(HashTable *hashTable);
void freeHashTable_static_all(HashTable* hashTable, void (*freeValue)(void*));
bool resizeHashTable(HashTable* hashTable, size_t newCapacity);

static inline size_t get_size_HashTable(HashTable *hashTable);
static inline size_t get_capacity_HashTable(HashTable *hashTable);

char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length);
unsigned char* base64_decode(const char* data, size_t input_length, size_t* output_length);
```

----

Su uso son los siguientes:

```C
HashTable* createHashTable(size_t size);
``` 
Esta funcion se encarga de crear una tabla de hash, del tamaño de `size`.
La tabla de hash tienen un capacidad especifica, pero se podra autoredimensionar,
mientras se agrege elmentos a traves de `put_static` o de `put_static_struct`.
Alternativamente, puedes llamar tu a `resizeHashTable` para redimensionar la tabla de hash, use la via que use, hay que aclarar que la redimension es cara, es necesario recalcular todos los hash's de cada entrada y copiar los elementos de la antigua tabla a la nueva. Se recomienda crear una tabla de hash con el tamaño que usted necesite, y no hacer demasiadas redimensiones. Por defecto las funciones `put` anteriores, redimensionan la tabla de hash al doble del tamaño original.

----

```C
static inline unsigned long hash_djb2(register const char* str, register size_t size);
``` 
Esta funcion es usada por las funciones `get` y `put`, permite obtener el hash de un `string` o, si usa `base64_encode` con una estructura, podra obtener el hash de una estructura codificada en base 64.

----

```C
void *get_static(HashTable *hashTable, const char *key);
void* get_static_struct(HashTable* hashTable, void *key, size_t lenght_key);
``` 
Esta funcion te permite obtener los datos de la tabla hash mediante la key que uso para ingresar los mismos. La clave debe de ser de tipo cadena, si se quiere usar una estructura en lugar de una cadena, debe usar la variante `put_static_struct`, recomiendo no combinar ambas en una misma tabla de hash, si tu tabla de hash usa keys de tipo cadenas, usa solo las de este tipo, o podrias tener problemas.

----

```C
void put_static(HashTable *hashTable, const char *key, void *value);
void put_static_struct(HashTable* hashTable, void* key, size_t lenght_key, void* value);
``` 
Esta funcion le permite ingresar datos en la tabla hash. Puede usar una cadena como clave (`put_static`), o una estructura(`put_static_struct`).
Es necesario que usted libere la key usada aqui, si es que la reservo usando memoria dinamica, internamente, se realizara una copia de su clave(con `strdup`) que sera liberada al llamar a alguna de las funciones de liberacion.

----

```C
void printHashTable(HashTable *hashTable);
``` 
Esta funcion te permite hacer un dumpeo simple de la tabla de hash,
consideramos que las claves son todas de tipo cadena en esta funcion.

----

```C
void freeHashTable_static_struct(HashTable *hashTable);
``` 
Libera la tabla de hash con sus estructuras/entradas internas, pero los elementos contenidos en la tabla de hash, debera liberarlos el programador, si
es que los reservo usando memoria dinamica.

----

```C
void freeHashTable_static_all(HashTable* hashTable, void (*freeValue)(void*));
``` 
Libera la tabla de hash con sus estructuras/entradas internas y ademas, libera
los elementos contenidos en la tabla de hash, debe pasar una funcion que recibira el dato contenido en cada entrada de la hash table, este dato se liberara segun lo dicte su funcion.

----

```c
bool resizeHashTable(HashTable* hashTable, size_t newCapacity);
```
Permite redimensionar las tablas de hash de tamaño estatico, tenga en cuenta que esto es costoso, debemos recalcular los hash's de todas las entradas y copiar los valores de una tabla a otra.

----

```c
static inline size_t get_size_HashTable(HashTable *hashTable);
```
Permite obtener cuantos elementos hay ocupando la tabla de hash.

----

```c
static inline size_t get_capacity_HashTable(HashTable *hashTable);
```
Permite obtener la capacidad de la tabla de hash, la cual indica cuantos elementos puede haber en la tabla de hash, antes de ser redimensionada.

----

```c
char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length);
unsigned char* base64_decode(const char* data, size_t input_length, size_t* output_length);
```
Permite codificar y descodificar en base64:
```c
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
```

-----


Puede encontrar un ejemplo de uso de esta implememtacion en `code_hash-table.c`:

![code_hash-table](./img/hash-table.png)

----