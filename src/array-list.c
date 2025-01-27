#ifndef __ARRAY_LIST_C__
#define __ARRAY_LIST_C__
#include "array-list.h"

ArrayList *createArrayList(position _size, void * _value){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(ArrayList *, createArrayList)
                TYPE_DATA_DBG(position, "_size = %zu")
                TYPE_DATA_DBG(void *, "_value = %p")
            END_TYPE_FUNC_DBG,
            _size, _value);
    #endif
    ArrayList *self ;//= (ArrayList *)malloc(sizeof(ArrayList));
    debug_malloc(ArrayList, self, 1*sizeof(ArrayList));
    
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

void push_back_a(ArrayList *self, void * _data){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(ArrayList *, createArrayList)
                TYPE_DATA_DBG(position, "self = %p")
                TYPE_DATA_DBG(void *, "_data = %p")
            END_TYPE_FUNC_DBG,
            self, _data);
    #endif
    /*
     *  
     *  push_back_a(self, _data): Agrega un elemento al final del arreglo. 
     *  Recibe como parametros un puntero al objeto ArrayList (self)
     *  y el dato a agregar (_data).
     *  
     */
    if (!_data || !self) return;
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
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(ArrayList *, pop_back_a)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *  
     *  pop_back_a(self): Elimina el ultimo elemento del array.
     * 
     */
    if(!self && !self->Size) return;
    self->Array[--self->Size] = 0; 
}

void* get_element_a(ArrayList *self, position index) {
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void *, get_element_a)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
                TYPE_DATA_DBG(position, "index = %zu")
            END_TYPE_FUNC_DBG,
            self, index);
    #endif

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
        #ifdef DEBUG_ENABLE
            DEBUG_PRINT(DEBUG_LEVEL_WARNING,
                "#{FG:red}[#{FG:yellow}get_element_a#{FG:red}] #{FG:lred}Índice fuera de límites o ArrayList inválido#{FG:white}.\n");
        #endif
        return NULL; // Índice inválido o ArrayList nulo
    }

    // Devuelve el elemento en el índice solicitado
    return self->Array[index];
}


void *front(ArrayList *self){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void *, front)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
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
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void *, back_a)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
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
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , shrink_to_fit)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *  
     *  shrink_to_fit(self): Reduce la capacidad del 
     *  array para que coincida exactamente con la 
     *  cantidad de elementos almacenados.
     * 
     */
    if (!self && !self->Size && self->Size == self->Capacity) return;

    //void **ptr_new = (void **)malloc(sizeof(void *) * self->Size);
    void **ptr_new;
    debug_malloc(void*, ptr_new, self->Size*sizeof(void*));
    for(position i = 0; i < self->Size; i++) ptr_new[i] = self->Array[i];
    
    free(self->Array);
    self->Array = ptr_new;
    self->Capacity = self->Size;
    
}

void *Destroy(ArrayList *self){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void *, Destroy)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *  
     *  Destroy(self): Libera la memoria asignada para 
     *  el arreglo y destruye el objeto ArrayList. 
     *  Devuelve un puntero nulo.
     * 
     */
    if (self){
        free(self->Array);
        self->Array = NULL;
        return self->Array;
    } 
    return NULL;
}

void forEachOld(ArrayList *self){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , forEachOld)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
            END_TYPE_FUNC_DBG,
            self);
    #endif
    /*
     *  
     *  forEach(self): Imprime por pantalla la informacion 
     *  del arreglo, mostrando cada elemento y su posicion.
     * 
     */
    if(!self && !self->Size) {
        #ifdef DEBUG_ENABLE
            DEBUG_PRINT(DEBUG_LEVEL_WARNING,
                "forEach(): El puntero 'self' es NULL o el tamaño es 0.");
        #endif
        return;
    }
    printf_color("Vector info\n\n");
    for (position i = 0; i < self->Size; i++){
        printf_color("\t #{FG:lred}%ld#{FG:lwhite}. #{FG:lcyan}%zu\n", i , get_val(size_t, self->Array[i]));
    }
    printf_color("\n-----\n");
}

void forEachNew(ArrayList *self, void (*func)(void *)){
    #ifdef DEBUG_ENABLE
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , forEachNew)
                TYPE_DATA_DBG(ArrayList *, "self = %p")
                TYPE_DATA_DBG(void (*)(void *), "func = %p")
            END_TYPE_FUNC_DBG,
            func);
    #endif
    /*
     *  
     *  forEach(self): Imprime por pantalla la informacion 
     *  del arreglo, mostrando cada elemento y su posicion.
     * 
     */
    if(!self && !self->Size) {
        #ifdef DEBUG_ENABLE
            DEBUG_PRINT(DEBUG_LEVEL_WARNING,
                "forEach(): El puntero 'self' es NULL o el tamaño es 0.");
        #endif
        return;
    }

    for (position i = 0; i < self->Size; i++){
        func(self->Array[i]);
    }
}

#endif