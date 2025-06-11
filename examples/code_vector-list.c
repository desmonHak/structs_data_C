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

#define DEBUG_ENABLE 
#define __VECTOR_LIST_DEBBUG__

#include "time_code.h"
#include "vector-list.h"

int main()
{

    // Crear una matriz 3x3 utilizando la lista enlazada
    int rows = 3;
    int columns = 3;

    // Crear una lista enlazada de listas enlazadas
    LinkedList *matrix = createLinkedList();

    // Inicializar cada fila de la matriz como una lista enlazada
    for (int i = 0; i < rows; i++)
    {
        LinkedList *row = createLinkedList();
        insertNode(matrix, row);
    }

    // Rellenar la matriz con algunos datos de ejemplo
    for (int i = 0; i < rows; i++)
    {
        LinkedList *row = (LinkedList *)get_element_v(matrix, i);
        for (int j = 0; j < columns; j++)
        {
            int *data = (int *)malloc(sizeof(int));
            *data = i * columns + j; // Valor de ejemplo
            insertNode(row, data);
        }
    }

    // Acceder a los elementos de la matriz y mostrar su contenido
    for (int i = 0; i < rows; i++)
    {
        LinkedList *row = (LinkedList *)get_element_v(matrix, i);
        Node *current = row->head;
        while (current != NULL)
        {
            int *data = (int *)current->data;
            printf_color("%d ", *data);
            current = current->next;
        }
        printf_color("\n");
    }

    // Liberar la memoria de la matriz y sus elementos
    for (int i = 0; i < rows; i++)
    {
        LinkedList *row = (LinkedList *)get_element_v(matrix, i);
        Node *current = row->head;
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp->data); // Liberar memoria del elemento
            // free(temp);
        }
        freeLinkedList(row); // Liberar memoria de la lista enlazada
    }
    freeLinkedList(matrix); // Liberar memoria del vector de listas enlazadas

    LinkedList *list = createLinkedList();

    element_def_asg(int, n1, 10)
        element_def_asg(float, n2, 20.2)
            element_def_asg(char, n3, 'l')
                element_def_asg(int, n4, 50)
                    element_def_asg(int, n5, 60)

                        insertNode(list, n1);
    insertNode(list, n2);
    insertNode(list, n3);
    insertNode(list, n4);
    insertNode(list, n5);

    printf_color("%d\n", get_element(int, list, 0));
    printf_color("%f\n", get_element(float, list, 1));
    printf_color("%c\n", get_element(char, list, 2));

    printf_color("Lista enlazada: ");
    printLinkedList(list);

    deleteNodeID(list, 1);
    deleteNodeID(list, 4);

    printf_color("Lista enlazada despues de eliminar nodos: ");
    printLinkedList(list);

    printf_color("pop_back: %d\n", pop_back(list));
    printLinkedList(list);

    printf_color("push_back: %d\n", push_back(list, n1));
    printLinkedList(list);

    position na = push_back(list, n1);
    printf_color("push_back: %d\n", na);
    printLinkedList(list);

    printf_color("posicion: %d\n", get_position(get_node(list, na)));

    printf_color("push_back: %d\n", push_back(list, n1));
    printLinkedList(list);

    Node *my_last_node = get_last_node(list);
    exists(list,my_last_node);
    printf_color("last position: %zu\n", get_last_position(list));
    void *my_data = get_last(list);
    printf("my_last_node->data = %p\n", my_data);

    deleteNode(list, my_last_node);

    deleteNodeID(list, 4);
    printLinkedList(list);
    if(existsID(list, 4)){
        puts("ID 4 existe");
        if(exists(list, get_node(list, 4))){
            puts("Nodo con ID 4 existe");
        }else {
        puts("Nodo con ID no 4 existe");
        deleteNode(list,get_node(list, 4));
    }
    } else {
        puts("ID no 4 existe");
    }

    if(empty(list)){
        puts("lista no vacia");
    }else{
        puts("lista vacia");
    }

    insertNode(list, n5);
    insertNode(list, n5);
    insertNode(list, n5);
    printf_color("size del vector: %d\n", size_v(list));

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);

    freeLinkedList(list);
    list = nullptr;

    printLinkedList(list);

    return 0;
}