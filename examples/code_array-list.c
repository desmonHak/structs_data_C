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