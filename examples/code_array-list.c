#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE
#endif
 
#include "time_code.h"
#include "array-list.h"

int main(){

    ArrayList *array = createArrayList(0, 0);

    element_def_asg(char*, n1, "hola mundo")
    element_def_asg(long long, n2, 11LL)
    element_def_asg(long long, n3, 12LL)
    element_def_asg(long long, n4, 14LL)
    element_def_asg(long long, n5, 189LL)
    element_def_asg(long long, n6, 19LL)

    push_back(array, n1);
    push_back(array, n2);
    push_back(array, n3);
    push_back(array, n4);
    push_back(array, n5);
    push_back(array, n6);
    //push_back(&array, 15LL);
    //push_back(&array, 105LL);
    //push_back(&array, 13355LL);

    //pop(&array);

    /*for (position i = 0; i < size(&array);i++){
        printf_color("\t%zu\n", array.Array[i]);
    }*/


    printf_color("El front del vector es %s\n", get_val(char*, front(array)));
    void *ptr = back(array);
    if (ptr != NULL){
        
        printf_color("El back del vector es %zu\n", get_val(size_t, ptr));
    }

    printf_color("Antes del shrinking\n");
    printf_color("El size del vector es %zu\n", size(array));
    printf_color("El capacity del vector es %zu\n", capacity(array));

    shrink_to_fit(array);

    printf_color("Despues del shrinking\n");
    printf_color("El size del vector es %zu\n", size(array));
    printf_color("El capacity del vector es %zu\n", capacity(array));

    element_def_asg(long long, n7, 89LL)
    push_back(array, n7);
    printf_color("Despues del push_back\n");
    printf_color("El size del vector es %zu\n", size(array));
    printf_color("El capacity del vector es %zu\n", capacity(array));
    
    forEach(array);

    pop_back(array);
    forEach(array);

    Destroy(array);

    printf_color("\n");

}