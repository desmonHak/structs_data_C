#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE
#endif

#define __VECTOR_LIST_DEBBUG__

#include "time_code.h"
#include "vector-list.h"

int main(){

    LinkedList *list = createLinkedList();
    ArrayList *array = createArrayList(0, 0);
    
    element_def_asg(char*, n1, "hola mundo")
    element_def_asg(long long, n2, 11LL)

    push_back_a(array, n1);
    push_back_a(array, n2);

    push_back_v(list, n1);
    push_back_v(list, n2);

    printf_color("El front del vector es %s\n", get_val(char*, front(array)));
    printf_color("El back del vector es %lld\n", get_val(long long, back(array)));

    printf_color("%s\n", get_element(char*, list, 0));
    printf_color("%lld\n", get_element(long long, list, 1));

    printf_color("size vector-list: %zu\n", size(list));
    printf_color("size array-list: %zu\n", size(array));

    pop_back(list);
    printf_color("size vector-list: %zu\n", size(list));
    printf_color("size array-list: %zu\n", size(array));

    pop_back(array);
    printf_color("size vector-list: %zu\n", size(list));
    printf_color("size array-list: %zu\n", size(array));

    Destroy(array);

    return 0;
}