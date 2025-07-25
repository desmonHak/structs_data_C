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

    // si se aplica esta funcion, no debe volver a liberase list
    //free_all_vector();
    freeLinkedList(list);

    free(array);


    free(n1);
    free(n2);

    return 0;
}