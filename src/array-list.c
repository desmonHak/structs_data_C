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

#ifndef __ARRAY_LIST_C__
#define __ARRAY_LIST_C__
#include "array-list.h"

#include "vector-list.h"

ArrayList *createArrayList(position _size, void * _value){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(ArrayList *, createArrayList)
            TYPE_DATA_DBG(position, "_size = %zu")
            TYPE_DATA_DBG(void *, "_value = %p")
        END_TYPE_FUNC_DBG,
        _size, _value);
    ArrayList *self = NULL;//= (ArrayList *)malloc(sizeof(ArrayList));
    debug_malloc(ArrayList, self, 1*sizeof(ArrayList));
    if (self == NULL) return NULL;
    
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
    self->Size = self->Capacity = _size;
    //self->Array = (void**)malloc(self->Capacity*sizeof(void*));
    if (self->Capacity) debug_malloc(void*, self->Array, self->Capacity*sizeof(void*));
    if (self->Array == NULL) DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}createArrayList#{FG:red}] #{FG:lred}Error malloc#{FG:white}: Error alloc #{FG:lgreen}%zu#{FG:white} bytes#{FG:lgreen}#{FG:white}.\n", self->Capacity * sizeof(void*));

    for(position i = 0; i < _size; i++){
        //printf_color("aaa %p %d", self->Array, self->Capacity*sizeof(void*));
        self->Array[i] = _value;
    }
    return self;
}

/*
 * Librea la memoria de una estructura ArrayList junto a su array dinamico. El programador debe liberar los
 * elementos internos del array por su cuentas, antes de liberar la memoria de este array.
 */
void freeArrayList_struct(ArrayList **self) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
    INIT_TYPE_FUNC_DBG(void, freeArrayList)
        TYPE_DATA_DBG(ArrayList **, "self = %p")
    END_TYPE_FUNC_DBG,
    self);
    if (self == NULL || *self == NULL) return;
    ArrayList *self_ = *self;

    if(self_->Array != NULL) free(self_->Array); // liberar la memoria del array dinamico
    free(self_); // liberar la memoria del objeto ArrayList

    *self = NULL; // no dejar puntero colgante
}

/*
 * Permite liberar la memoria de una estructura ArrayList, su array dinamico y todos sus elementos internos.
 * usando una función de liberación personalizada para cada elemento interno.
 */
void freeArrayListAndElements(ArrayList **self, void (*free_func)(void *)) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
    INIT_TYPE_FUNC_DBG(void, freeArrayListAndElements)
        TYPE_DATA_DBG(ArrayList **, "self = %p")
        TYPE_DATA_DBG(void (*)(void *), "free_func = %p")
    END_TYPE_FUNC_DBG,
    self, free_func);
    if (free_func == NULL) return;
    if (self == NULL || *self == NULL) return;
    ArrayList *self_ = *self;

    for (register size_t i = 0; i < self_->Size; i++) {
        free_func(self_->Array[i]); // liberar la memoria del elemento interno
    }

    if(self_->Array != NULL) free(self_->Array); // liberar la memoria del array dinamico
    free(self_); // liberar la memoria del objeto ArrayList

    *self = NULL; // no dejar puntero colgante
}

void push_back_a(ArrayList *self, void * _data){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(ArrayList *, createArrayList)
            TYPE_DATA_DBG(position, "self = %p")
            TYPE_DATA_DBG(void *, "_data = %p")
        END_TYPE_FUNC_DBG,
        self, _data);
    /*
     *  
     *  push_back_a(self, _data): Agrega un elemento al final del arreglo. 
     *  Recibe como parametros un puntero al objeto ArrayList (self)
     *  y el dato a agregar (_data).
     *  
     */
    if (_data == NULL || self == NULL) return;
    if (!self->Size){
        self->Size = self->Capacity = 1;
        //self->Array = (void **)malloc(sizeof(void*) * self->Capacity);
        debug_malloc(void*, self->Array, self->Capacity*sizeof(void*));
        //DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}push_back_a#{FG:red}] #{FG:white}Capacity update to: #{FG:lgreen}%zu#{FG:white}.", self->Capacity);
        self->Array[0] = _data;
    } else if (self->Size == self->Capacity){
        self->Capacity *= __ADD_CAPACITY__;
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}push_back_a#{FG:red}] #{FG:white}Capacity update to: #{FG:lgreen}%zu#{FG:white}.\n", self->Capacity);
        //void **ptr_new = (void **)malloc(sizeof(void*) * self->Capacity);
        void **ptr_new;
        debug_malloc(void*, ptr_new, self->Capacity*sizeof(void*));

        for(register position i = 0; i < self->Size; i++) ptr_new[i] = self->Array[i];

        free(self->Array);
        self->Array = ptr_new;
        self->Array[self->Size++] = _data;
    } else self->Array[self->Size++] = _data;
}



void pop_back_a(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(ArrayList *, pop_back_a)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);
    /*
     *  
     *  pop_back_a(self): Elimina el ultimo elemento del array.
     * 
     */
    if(!self && !self->Size) return;
    self->Array[--self->Size] = 0; 
}

void* get_element_a(ArrayList *self, position index) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void *, get_element_a)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
            TYPE_DATA_DBG(position, "index = %zu")
        END_TYPE_FUNC_DBG,
        self, index);

    /*
     *  
     *  get_element_a(self, index): Devuelve un elemento del ArrayList.
     *  Recibe como parámetros un puntero al ArrayList (self) y el índice del
     *  elemento que se desea obtener (index).
     *  
     *  Si el índice está fuera de los límites, la función devuelve NULL.
     * 
     */

    // Validar el puntero del ArrayList y los límites del índice
    if (!self || index >= self->Size) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "#{FG:red}[#{FG:yellow}get_element_a#{FG:red}] #{FG:lred}Índice fuera de límites o ArrayList inválido#{FG:white}.\n");
        return NULL; // Índice inválido o ArrayList nulo
    }

    // Devuelve el elemento en el índice solicitado
    return self->Array[index];
}


void *front(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void *, front)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);
    /*
     *  
     *  front(self): Devuelve el primer 
     *  elemento del array.
     * 
     */
    if(self && self->Size) return self->Array[0];
    return NULL; // el vector esta vacio
}

void *back_a(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void *, back_a)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);
    /*
     *  
     *  back_a(self): Devuelve el ultimo elemento 
     *  del array.
     * 
     */
    if(self && self->Size) return self->Array[self->Size -1];
    else return NULL; // el vector esta vacio
}

void shrink_to_fit(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void , shrink_to_fit)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);
    /*
     *  
     *  shrink_to_fit(self): Reduce la capacidad del 
     *  array para que coincida exactamente con la 
     *  cantidad de elementos almacenados.
     * 
     */
    if (self == NULL || self->Size == 0 || self->Size == self->Capacity) return;

    //void **ptr_new = (void **)malloc(sizeof(void *) * self->Size);
    void **ptr_new;
    debug_malloc(void*, ptr_new, self->Size*sizeof(void*));
    for(position i = 0; i < self->Size; i++) ptr_new[i] = self->Array[i];
    
    free(self->Array);
    self->Array = ptr_new;
    self->Capacity = self->Size;
    
}

/**
 * Destroy(self): Libera la memoria asignada al arreglo, perno destruye el objeto ArrayList,
 * debe liberarlo el programador. Devuelve un puntero nulo.
 * @param self Array list del que liberar la lista, mas no los objetos de esta.
 * @return puntero nulo con la memoria liberada
 */
void *Destroy(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void *, Destroy)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);

    if (self){
        free(self->Array);
        self->Array = NULL;
        
        return self->Array;
    }
    return NULL;
}

void forEachOld(ArrayList *self){
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void , forEachOld)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
        END_TYPE_FUNC_DBG,
        self);
    /*
     *  
     *  forEach(self): Imprime por pantalla la informacion 
     *  del arreglo, mostrando cada elemento y su posicion.
     * 
     */
    if(!self && !self->Size) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "forEach(): El puntero 'self' es NULL o el tamaño es 0.");
        return;
    }
    printf_color("Vector info\n\n");
    for (position i = 0; i < self->Size; i++){
        printf_color("\t #{FG:lred}%ld#{FG:lwhite}. #{FG:lcyan}%zu\n", i , get_val(size_t, self->Array[i]));
    }
    printf_color("\n-----\n");
}

void forEachNew(ArrayList *self, void (*func)(void *)){
    /*
     *  
     *  forEach(self): Imprime por pantalla la informacion 
     *  del arreglo, mostrando cada elemento y su posicion.
     * 
     */
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
        INIT_TYPE_FUNC_DBG(void , forEachNew)
            TYPE_DATA_DBG(ArrayList *, "self = %p")
            TYPE_DATA_DBG(void (*)(void *), "func = %p")
        END_TYPE_FUNC_DBG,
        func);

    if (func == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "forEachNew(): La función de callback es NULL.");
        return;
    }
    if (self == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "forEach(): El puntero 'self' es NULL.");
        return;
    }
    if(self->Size <= 0) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "forEach(): el tamaño es 0.");
        return;
    }
    if (self->Array == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_WARNING,
            "forEach(): La memoria para el arreglo es NULL.");
        return;
    }

    for (position i = 0; i < self->Size; i++){
        func(self->Array[i]);
    }
}

#endif