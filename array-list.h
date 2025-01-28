/*
 *	Licencia Apache, Versión 2.0 con Modificación
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

#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "debug_c.h"

#ifndef push_back
#define push_back(array, ...) _Generic((array), \
    ArrayList*: push_back_a,                      \
    default: push_back_a)(array,__VA_ARGS__)
#endif

#ifndef pop_back
#define pop_back(list) _Generic((list), \
    ArrayList*: pop_back_a)(list)               
#endif

#ifndef size
#define size(list) _Generic((list), \
    ArrayList*: size_a)(list)                  
#endif

#ifndef back
#define back(list) _Generic((list), \
    ArrayList*: back_a)(list)               
#endif

// definicion:
#define element_def(type, name) \
    type *name; \
    debug_malloc(type, name, sizeof(type));
    //type *name = (type *)malloc(sizeof(type));

// asignacion
#define element_asg(name, value) \
    *name = value;

// definicion y asignacion:
#define element_def_asg(type, name, value)     \
    type *name; \
    debug_malloc(type, name, sizeof(type)); \
    *name = value;
    //type *name = (type *)malloc(sizeof(type)); 

#define get_val(type, name) *((type *)(name))

typedef size_t position;
typedef struct {
    position Size, Capacity;
    void **Array;
    /*struct {
        
    } func;*/
} ArrayList;

//typedef ArrayList* (*createArrayListPtr)(ArrayList*, position, void*);

/*
 *  
 *  createArrayList(self, _size, _value): Esta funcion se 
 *  encarga de construir un objeto ArrayList. 
 *  Recibe como parametros un puntero al objeto ArrayList (self),
 *  el tamaño inicial del array (_size), y el valor con el 
 *  que se llenará el array (_value). La funcion asigna 
 *  memoria para el array y lo inicializa con el valor especificado. 
 *  Esta funcion devuelve un puntero al objeto ArrayList construido.
 *  
 */
ArrayList *createArrayList(position _size, void *_value);

/*
 *  
 *  push_back_a(self, _data): Agrega un elemento al final del arreglo. 
 *  Recibe como parametros un puntero al objeto ArrayList (self)
 *  y el dato a agregar (_data).
 *  
 */
void push_back_a (ArrayList *self, void *_data);

/*
 *  
 *  pop_back_a(self): Elimina el ultimo elemento del array.
 * 
 */
void pop_back_a(ArrayList *self);

/*
 *  
 *  shrink_to_fit(self): Reduce la capacidad del 
 *  array para que coincida exactamente con la 
 *  cantidad de elementos almacenados.
 * 
 */
void shrink_to_fit(ArrayList *self);

/*
 *  
 *  size_a(self): Devuelve la cantidad de 
 *      elementos almacenados en el array.
 * 
 */
static inline position size_a(ArrayList *self){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(position, size_a)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *  
     *  size_a(self): Devuelve la cantidad de 
     *      elementos almacenados en el array.
     * 
     */
    return self->Size;
}

/*
 *
 *  capacity(self): Devuelve la capacidad actual del array, 
 *  el tamaño maximo que puede alcanzar sin necesidad de 
 *  redimensionarlo.
 * 
 */
static inline position capacity(ArrayList *self){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(position, capacity)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *
     *  capacity(self): Devuelve la capacidad actual del array, 
     *  el tamaño maximo que puede alcanzar sin necesidad de 
     *  redimensionarlo.
     * 
     */
    return self->Capacity;
}

/*
 *  
 *  back_a(self): Devuelve el ultimo elemento 
 *  del array.
 * 
 */
void *back_a(ArrayList *self);

/*
 *  
 *  front(self): Devuelve el primer 
 *  elemento del array.
 * 
 */
void *front(ArrayList *self);

/*
 *  
 *  Destroy(self): Libera la memoria asignada para 
 *  el arreglo y destruye el objeto ArrayList. 
 *  Devuelve un puntero nulo.
 * 
 */
void *Destroy(ArrayList *self);

// liberar la estructura y su array dinamico
void freeArrayList_struct(ArrayList **self);

// liberar la estructura, su array dinamico y los elementos internos
void freeArrayListAndElements(ArrayList **self, void (*free_func)(void *));

/*
 *  
 *  forEach(self): Imprime por pantalla la informacion 
 *  del arreglo, mostrando cada elemento y su posicion.
 * 
 */
void forEachOld(ArrayList *self);
void forEachNew(ArrayList *self, void (*func)(void *));

void* get_element_a(ArrayList *self, position index);

// Macro para detectar número de argumentos
#ifndef GET_MACRO
#define GET_MACRO(_1, _2, NAME, ...) NAME
#endif
#ifndef forEach
#define forEach(...) GET_MACRO(__VA_ARGS__, forEachNew, forEachOld)(__VA_ARGS__)
#endif

#ifndef freeArrayList
#define freeArrayList(...) GET_MACRO(__VA_ARGS__, freeArrayListAndElements, freeArrayList_struct)(__VA_ARGS__)
#endif

#ifndef __ADD_CAPACITY__
#define __ADD_CAPACITY__ 2
#endif

#ifdef INCLUDE_COLORS_C
#include "array-list.c"
#endif
#endif