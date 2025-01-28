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

#ifndef __MATRIZ_LIST_C__
#define __MATRIZ_LIST_C__
#include "matriz-list.h"

position calcularPosicionVector(const dimensiones *dimensiones_, const position *coordenada, const position numDimensiones) {
    if (dimensiones_ == NULL || coordenada == NULL) return 0;
    position posicion = 0;
    position potencia = 1;

    for (position i = numDimensiones - 1; i > 0; i--) {
        posicion += coordenada[i] * potencia;
        potencia *= dimensiones_[i];
    }

    return posicion;
}
Matriz *createMatriz(dimensiones dimensionesMatriz, ...)
{
    // crea una matriz multidimensional
    va_list args;
    va_start(args, dimensionesMatriz);

    Matriz *my_matriz = newMatriz();

    va_list copy1;
    va_copy(copy1, args);

    // numero de argumentos que tiene la funcion:
    position n_args = 0;
    while (va_arg(copy1, position))
    {
        n_args++;
    }

    va_copy(copy1, args);
    // calcular la cantidad de elementos para la matriz:
    position totalElements = get_size_va_list(dimensionesMatriz, copy1);
    printf_color("\ntotalElements: %p == %zu\n ", (void*)totalElements, totalElements);

    va_copy(copy1, args);
    my_matriz->dimensiones_matriz = dimensiones_matriz_va_list(dimensionesMatriz, copy1);
    my_matriz->list = createArrayList(totalElements, NULL);
    if (!my_matriz->list || !my_matriz->dimensiones_matriz) {
        puts("Error creando la matriz!");
        freeMatriz(my_matriz);
        return NULL;
    };

    /*for(position i = 0; i < totalElements; i++){
        printf_color("createArrayList: \n ");
        ArrayList *a = createArrayList(totalElements, NULL);
        printf_color("totalElements: %p\n ", a);
        
        get_element(void*, my_matriz->list, (void*)a);
        printf_color("s: %p\n ", a);
    }*/

    printf_color("totalElements: %zu\n ", totalElements);

    va_end(copy1);
    va_end(args);

    return my_matriz;
}

dimensiones get_size_matriz(Matriz* self){
    if (self == NULL || self->list == NULL) return 0;
    return size_a(self->list);
}

dimensiones get_size_total_calc(dimensiones dimensionesMatriz, ...)
{
    // obtiene la cantidad de elementos totales teoricos que puede tener una matriz:
    va_list args;
    va_start(args, dimensionesMatriz);
    position totalElements = get_size_va_list(dimensionesMatriz, args);
    va_end(args);
    return totalElements;
}

dimensiones get_size_va_list(dimensiones dimensionesMatriz, va_list args)
{
    // obtiene la cantidad de elementos totales teoricos que puede tener una matriz:
    position totalElements = 1;
    for (position i = 0; i < dimensionesMatriz; i++)
    {
        position num = va_arg(args, position);
        totalElements *= num;
        printf_color("(%zu), ", num);
    }
    return totalElements;
}

ArrayList *dimensiones_matriz_va_list(dimensiones dimensionesMatriz, va_list args)
{
    if (dimensionesMatriz == 0) return NULL;
    ArrayList *my_dimension = createArrayList(dimensionesMatriz, NULL);
    if (!my_dimension) return NULL;
    for (position i = 0; i < dimensionesMatriz; i++)
    {
        element_def_asg(dimensiones, dimension, va_arg(args, position));
        push_back(my_dimension, dimension);
    }
    return my_dimension;
}

ArrayList *dimensiones_matriz(dimensiones dimensionesMatriz, ...)
{
    va_list args;
    va_start(args, dimensionesMatriz);
    ArrayList *my_dimension = dimensiones_matriz_va_list(dimensionesMatriz, args);
    va_end(args);
    if (!my_dimension) return NULL;
    return my_dimension;
}

Matriz *newMatriz()
{
    // crea un matrix vacia, vector(fila = row) para almacenar las columnas(columns)
    Matriz *my_matriz = (Matriz *)malloc(sizeof(Matriz));
    my_matriz->dimensiones_matriz = dimensiones_matriz_va_list(0, NULL);
    my_matriz->list = NULL;
    return my_matriz;
}
/*
void createColumns(Matriz *matriz, position columns)
{
    // Crea una nueva columna en la matriz con el número de elementos especificado

    for (position i = 0; i < columns; i++)
    {
        ArrayList *column = createArrayList();
        push_back(matriz->list, column);
    }
}

void createRow(Matriz *matriz, position row)
{
    // Crea una nueva fila en la matriz con el número de elementos especificado

    ArrayList *rowList = createArrayList();

    for (position i = 0; i < row; i++)
    {
        ArrayList *column = get_element_v(matriz->list, i);
        push_back(rowList, column);
    }

    push_back(matriz->list, rowList);
}*/

Matriz* freeMatriz(Matriz *matriz)
{
    if (matriz == NULL) return NULL;
    // liberar el array que contiene todos los elementos de la matriz:
    if(matriz->list != NULL) {
        for (position i = matriz->list->Size; i > 0 ; i--){
            // obtener el ultimo elemento del vector y liberarlo:
            void *ptr = back_a(matriz->dimensiones_matriz);
            if (ptr == NULL) {
                free(ptr); continue;
            }
            // eliminar el elemento del vector:
            pop_back_a(matriz->list);
        }
        Destroy(matriz->list); 
    }
    
    // liberar el array que guarda las dimensiones de la matriz:
    if(matriz->dimensiones_matriz != NULL) {
        for (position i = matriz->list->Size; i > 0 ; i--){
            // obtener el ultimo elemento del vector y liberarlo:
            void *ptr = back_a(matriz->dimensiones_matriz);
            if (ptr == NULL) {
                free(ptr); continue;
            }
            // eliminar el elemento del vector:
            pop_back_a(matriz->dimensiones_matriz);
        }
        Destroy(matriz->dimensiones_matriz);
    }
    
    free(matriz);
    return NULL; // retornar nulo 
}

#endif