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
#include "matriz-list.h"

// -Wall -Werror -Wpedantic -x c  -time  -save-temps -g

int main()
{

    // int arr[2 + 2*4+ 5 *4*5];

    /*int arr2[2][4][5] = {
        {
            {1, 2, 3, 4, 5},
            {5, 4, 3, 2, 1},
            {1, 2, 3, 4, 5},
            {5, 4, 3, 2, 1},
        },
        {
            {1, 2, 3, 4, 5},
            {5, 4, 3, 2, 1},
            {1, 2, 3, 4, 5},
            {5, 4, 3, 2, 1},
        }};
        size_t i = sizeof(arr2)/sizeof(int);*/

    //int arr1[2+ 2*4 + (2+2*4)*5] = {
    char arr1[2+ 2*4 + (2+2*4)*5] = { 
        1, 2, 3,  4,  5,
        2, 3, 5,  9,  13,
        3, 5, 8,  13, 21,
        4, 9, 14, 22, 35,

        1, 2, 3, 4, 5,
        5, 4, 3, 2, 1,
        1, 2, 3, 4, 5,
        5, 4, 3, 2, 1,
    };
    // sizeof(arr1)

    // f(arr1, a, b, c) -> (a * y*x) % (z*y*x) + (b * x) % (y * x) + c % x
    
    (void)printf_color("arr1[%u] = %d; %d\n",((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) , *(((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) +arr1),0);
    (void)printf_color("arr1[%u] = %d; %d\n",((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) , arr1[((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5)],0);
//% 4*5,% 5, malloc(( (1 * 4*5) + ((3 * 5) ) + 4 ) * sizeof(int))
    // crear una matriz tridimensional de 5x5x5
    Matriz *my_matriz = createMatriz(4, 5, 5, 5, 5);
    //Matriz *my_matriz = createMatriz(3, 5, 5, 5);


    (void)printf_color("get_size_total_calc: %zu\n", get_size_total_calc(4, 5, 5, 5, 5));
    (void)printf_color("get_size_matriz: %zu\n", get_size_matriz(my_matriz));
    //forEach(my_matriz->dimensiones_matriz);
    //forEach(my_matriz->list);
    void *ptr = front(my_matriz->list);
    if (!ptr){
        printf_color("El front del vector es %zu\n", *((position *)(my_matriz->list->Array)));
        printf_color("El front del vector es %zu\n", get_val(position, ptr));
    } else {
        printf_color("El front del vector es NULL, %p\n", (void *)my_matriz->list);
    }
    
    my_matriz = freeMatriz(my_matriz);
    (void)puts("memoria liberada");

    return 0;
}
