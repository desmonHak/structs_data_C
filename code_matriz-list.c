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
    
    (void)printf("arr1[%u] = %d; %d\n",((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) , *(((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) +arr1),0);
    (void)printf("arr1[%u] = %d; %d\n",((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5) , arr1[((0 * 4*5 ) % (2*4*5) + (3 * 5) % (4*5) + 4 % 5)],0);
//% 4*5,% 5, malloc(( (1 * 4*5) + ((3 * 5) ) + 4 ) * sizeof(int))
    // crear una matriz tridimensional de 5x5x5
    Matriz *my_matriz = createMatriz(4, 5, 5, 5, 5);
    //Matriz *my_matriz = createMatriz(3, 5, 5, 5);


    (void)printf("get_size_total_calc: %zu\n", get_size_total_calc(4, 5, 5, 5, 5));
    (void)printf("get_size_matriz: %zu\n", get_size_matriz(my_matriz));
    
    my_matriz = freeMatriz(my_matriz);
    (void)puts("memoria liberada");

    return 0;
}
