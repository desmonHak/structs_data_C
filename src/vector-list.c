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

#ifndef __VECTOR_LIST_C__
#define __VECTOR_LIST_C__

#include "vector-list.h"

void __attribute__((constructor)) __constructor_array_dinamic__() {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void __attribute__((constructor)), __constructor_array_dinamic__)
                    END_TYPE_FUNC_DBG);

    debug_malloc(LinkedList, table_matriz_, sizeof(LinkedList));
    table_matriz_->head = NULL;
    table_matriz_->lastId = 0;
}

#ifndef DISABLE__destructor_array_dinamic__
void __attribute__((destructor)) __destructor_array_dinamic__() {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void __attribute__((destructor)), __destructor_array_dinamic__)
                    END_TYPE_FUNC_DBG);

    free_all_vector();
    // Free the table_matriz_ structure itself, but NOT the nodes or data they point to.
    free(table_matriz_);
    table_matriz_ = NULL; // prevent use after free
#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}__destructor_array_dinamic__#{FG:red}] #{FG:white} Tabla de vectores liberada exitosamente. \n");
#endif
}
#endif


void free_all_vector() {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, free_all_vector)
                    END_TYPE_FUNC_DBG);

    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}free_all_vector#{FG:white}()\n");

    if (table_matriz_ == NULL) return;

    Node *current = table_matriz_->head;
    Node *next;

    while (current != NULL) {
        next = current->next; // Store the next pointer
        LinkedList *vector = (LinkedList *)current->data;

        if (vector != NULL) {
#ifdef __VECTOR_LIST_DEBBUG__
            printLinkedList(vector);
#endif
            freeLinkedList(vector); // Free the linked list "vector" itself.
        }

        // Now free the node in table_matriz_
        free(current);

        current = next; // Advance to the next node
    }

    table_matriz_->head = NULL; // Reset the head pointer
    table_matriz_->lastId = 0;  // Reset lastId
}


Node *get_node(LinkedList *list, const position pos) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(Node *, get_node)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(const position, "pos = %d")
                    END_TYPE_FUNC_DBG,
                list, pos);

    if (list == NULL || pos < 0) {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}get_node#{FG:red}] #{FG:white} Lista invalida o posicion invalida \n");
        return NULL;
    }

    Node *current = list->head;
    position i = 0; // Use a counter
    while (current != NULL && i < pos) {
        current = current->next;
        i++;
    }

    return current;
}


const position get_position(Node *node)
{
        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , get_position)
                TYPE_DATA_DBG(Node *, "node = %p")
            END_TYPE_FUNC_DBG,
            node);
    if (node == NULL) return -1; // Nodo nulo, posición inválida
    return node->id;
}

LinkedList *createLinkedList() {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(LinkedList *, createLinkedList)
                    END_TYPE_FUNC_DBG);

    LinkedList *list;
    debug_malloc(LinkedList, list, sizeof(LinkedList));
    list->head = NULL;
    list->lastId = 0;

    insertNode(table_matriz_, list);
#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}createLinkedList#{FG:red}] #{FG:white} Registro de vectores reservados en run time (table_matriz_): \n");
    printLinkedList(table_matriz_);
#endif

    return list;
}


void *get_element_v(LinkedList *list, const position ID) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void *, get_element_v)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(const position, "ID = %u")
                    END_TYPE_FUNC_DBG,
                list, ID);

    if (list == NULL) return NULL;

    Node *current = list->head;
    while (current != NULL) {
        if (current->id == ID) {
            DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_element_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}const position #{FG:white}ID#{FG:white}) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p\n;", current->data);
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}


void insertNode(LinkedList *list, void *data) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, insertNode)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(void *, "data = %u")
                    END_TYPE_FUNC_DBG,
                list, data);

    if (list == NULL || data == NULL) return;

    Node *newNode;
    debug_malloc(Node, newNode, sizeof(Node));

    newNode->id = list->lastId++;
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}insertNode#{FG:red}] #{FG:white}Data insert in node with ID: #{FG:lgreen}%zu#{FG:white}.\n", newNode->id);

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool existsID(LinkedList *list, const position ID) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, existsID)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(const position, "ID = %u")
                    END_TYPE_FUNC_DBG,
                list, ID);

    if (list == NULL) return false;

    Node *current = list->head;
    while (current != NULL) {
        if (current->id == ID) {
            return true;
        }
        current = current->next;
    }
    return false;
}


bool exists(LinkedList *list, Node *node) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(bool, exists)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(Node *, "node = %p")
                    END_TYPE_FUNC_DBG,
                list, node);

    if (list == NULL || node == NULL) return false;

    Node *current = list->head;
    while (current != NULL) {
        if (node == NULL)
            break;
        if (current == node) {
            DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred} bool#{FG:cyan} exists#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}Node #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}true\n");
            return true;
        }
        current = current->next;
    }
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}bool #{FG:cyan}exists#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}Node #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}false\n");
    return false;
}


void deleteNode(LinkedList *list, Node *node) {
    DEBUG_PRINT(DEBUG_LEVEL_INFO,
                INIT_TYPE_FUNC_DBG(void, deleteNode)
                    TYPE_DATA_DBG(LinkedList *, "list = %p")
                    TYPE_DATA_DBG(Node *, "node = %p")
                    END_TYPE_FUNC_DBG,
                list, node);

    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}deleteNode#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list = %p, #{FG:lyellow}Node* #{FG:white}node = %p#{FG:white})\n", list, node);

    if (list == NULL || list->head == NULL || node == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNode#{FG:red}] #{FG:white} La lista o el nodo son nulos. \n");
        return;
    }

    if (list->head == node) {
        list->head = list->head->next;
        free(node);
        updateIds(list);
        return;
    }

    Node *prev = list->head;
    Node *current = list->head->next;

    while (current != NULL && current != node) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        free(current);
        updateIds(list);
    } else {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNode#{FG:red}] #{FG:white} El nodo no se encontro en la lista. \n");
    }
}

int deleteNodeID(LinkedList *list, const position ID) {
    if (list == NULL || list->head == NULL) {
        return -1; // Or some other error code
    }

    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL) {
        if (current->id == ID) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);  // Free the node

            // Update IDs for subsequent nodes (important!)
            updateIds(list);
            return 0; // Success
        }
        previous = current;
        current = current->next;
    }
    return -1; // ID not found
}

void updateIds(LinkedList *list) {
    if (list == NULL || list->head == NULL) return;

    Node *current = list->head;
    position id = 0;

    while (current != NULL) {
        current->id = id++;
        current = current->next;
    }
    list->lastId = id;  // Update lastId to the new count
}


const position pop_back_v(LinkedList *list)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , pop_back_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    // Comprobar si la lista está vacía
    if (list == NULL || list->head == NULL)
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}pop_back_v#{FG:red}] #{FG:white} La lista esta vacia.\n");
        // La lista está vacía, retornar -1
        return -1;
    }
    // Comprobar si la lista tiene solo un nodo
    else if (list->head->next == NULL)
    {
        // Guardar el ID del único nodo
        position id = list->head->id;
        // Liberar el nodo
        free(list->head);
        // Establecer la cabeza de la lista como NULL
        list->head = NULL;
        // Restablecer el valor de lastId a 0
        list->lastId = 0;
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}pop_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", id);
        // Retornar el ID del nodo eliminado
        return id;
    }
    else
    {
        // Buscar el penúltimo nodo de la lista
        Node *current = list->head;
        while (current->next->next != NULL)
        {
            current = current->next;
        }
        // Guardar el ID del último nodo
        position id = current->next->id;
        // Liberar el último nodo
        free(current->next);
        // Establecer el siguiente del penúltimo nodo como NULL
        current->next = NULL;
        // Actualizar los IDs después de eliminar el nodo
        updateIds(list); 
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}pop_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", id);
        // Retornar el ID del nodo eliminado
        return id;
    }
}

const position push_back_v(LinkedList *list, void *data)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , push_back_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(void *, "data = %p")
            END_TYPE_FUNC_DBG,
            list, data);

    // Comprobar si la lista o los datos son inválidos
    if (list == NULL || data == NULL)
    {
        // La lista es inválida o los datos no son válidos, retornar -1
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}push_back_v#{FG:red}] #{FG:white} La lista es invalida o data no es valido. \n");
        return -1;
    }

    // Crear un nuevo nodo
    // Node *newNode = (Node *)malloc(sizeof(Node));
    Node *newNode;
    debug_malloc(Node, newNode, sizeof(Node));
    newNode->id = list->lastId++; // Asignar un ID al nuevo nodo
    newNode->data = data; // Establecer los datos del nuevo nodo
    newNode->next = NULL; // Establecer el siguiente del nuevo nodo como NULL

    // Insertar el nuevo nodo al final de la lista
    if (list->head == NULL)
    {
        // Si la lista está vacía, el nuevo nodo se convierte en la cabeza de la lista
        list->head = newNode;
    }
    else
    {
        // Si la lista no está vacía, buscar el último nodo
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        // Enlazar el nuevo nodo al final de la lista
        current->next = newNode;
    }
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}push_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}void* #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", newNode->id);
    // Retornar el ID del nuevo nodo agregado
    return newNode->id;
}

bool empty(LinkedList *list) {
    if (list == NULL) return true;
    return (list->head == NULL);
}


void clear(LinkedList *list)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , clear)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return;
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp); // Liberar la memoria del nodo actual
    }
    list->head = NULL; // Establecer la cabeza de la lista como NULL
    list->lastId = 0; // Restablecer el valor de lastId a 0
}

size_t size_v(LinkedList *list) {
    if (list == NULL) return 0;
    size_t count = 0;
    Node *current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void printLinkedList(LinkedList *list) {
    if (list == NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}printLinkedList#{FG:red}] #{FG:white} La lista es nula. \n");
        return;
    }
    Node *current = list->head;
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lgreen}Lista Enlazada: #{FG:white}[");
    while (current != NULL) {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "ID: %zu, Data: %p", current->id, current->data);
        if (current->next != NULL) {
            DEBUG_PRINT(DEBUG_LEVEL_INFO, ", ");
        }
        current = current->next;
    }
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "]#{FG:white}\n");
}


void freeLinkedList(LinkedList *list) {
    if (list == NULL) return;

    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);  // Free the node structure itself.
        current = next;
    }

    list->head = NULL;
    list->lastId = 0;

}

Node *get_last_node(LinkedList *list)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(Node * , get_last_node)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL || list->head == NULL)
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}get_last_node#{FG:red}] #{FG:white}Lista vacia\n");
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}Node #{FG:white}*#{FG:cyan}get_last_node#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", NULL);
        return NULL; // Lista vacía
    }

    Node *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}Node #{FG:white}*#{FG:cyan}get_last_node#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", current);
    return current;
}

void *get_last(LinkedList *list)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void * , get_last)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return NULL;
    Node *lastNode = get_last_node(list);
    if (lastNode != NULL)
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", lastNode->data);
        return lastNode->data;
    }
    else
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", NULL);
        return NULL;
    }
}

const position get_last_position(LinkedList *list)
{

        DEBUG_PRINT(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , get_last_position)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return 0;
    Node *lastNode = get_last_node(list);
    if (lastNode != NULL)
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%zu;\n", lastNode->id);
        return lastNode->id;
    }
    else
    {
        DEBUG_PRINT(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%zu;\n", -1);
        return -1; // Lista vacía
    }
}

#endif
