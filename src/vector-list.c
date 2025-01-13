#ifndef __VECTOR_LIST_C__
#define __VECTOR_LIST_C__

#include "vector-list.h"

void __attribute__((constructor)) __constructor_array_dinamic__()
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void __attribute__((constructor)) , __constructor_array_dinamic__)
            END_TYPE_FUNC_DBG
            );
    /*
     *
     *  Esta función es un constructor que se ejecutará automáticamente antes de que se inicie la ejecución
     *  del programa principal. Aquí se asigna memoria para la variable table_matriz_, que parece ser una
     *  instancia de la estructura LinkedList, y se inicializan sus miembros.
     *
     */
    // table_matriz_ = (LinkedList *)malloc(sizeof(LinkedList));
    debug_malloc(LinkedList, table_matriz_, sizeof(LinkedList));
    table_matriz_->head = NULL;
    table_matriz_->lastId = 0; // al crearse la lista la posicion incial es 0
}
#ifndef DISABLE__destructor_array_dinamic__
void __attribute__((destructor)) __destructor_array_dinamic__()
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void __attribute__((destructor)) , __destructor_array_dinamic__)
            END_TYPE_FUNC_DBG
            );
    /*
     *
     *  Esta función es un destructor que se ejecutará automáticamente al finalizar
     *  la ejecución del programa principal. Aquí se liberan los recursos asignados
     *  previamente, incluyendo la memoria ocupada por table_matriz_ y sus elementos
     *
     */
    /*#ifdef __VECTOR_LIST_DEBBUG__
        puts("liberando");
    #endif

        // Liberar los vectores almacenados en table_matriz_
        Node *current = table_matriz_->head;
        while (current != NULL && !empty(table_matriz_))
        {
            Node *next = current->next;
            LinkedList *vector = (LinkedList *)current->data;

            if (vector != NULL)
            {
                deleteNodeID(table_matriz_, current->id); // Eliminar el nodo de la tabla de vectores

                if (vector->head != NULL)
                {
                    freeLinkedList(vector); // Liberar el vector
                }
            }

            current = next;
        }
    #ifdef __VECTOR_LIST_DEBBUG__
        puts("vectores liberados");
    #endif
        // Liberar table_matriz_ en sí
        freeLinkedList(table_matriz_); // Liberar la tabla de vectores
    #ifdef __VECTOR_LIST_DEBBUG__
        puts("Tabla de vectores liberada exitosamente");
    #endif*/
    free_all_vector();
    // Liberar table_matriz_ en sí
    freeLinkedList(table_matriz_); // Liberar la tabla de vectores
#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}__destructor_array_dinamic__#{FG:red}] #{FG:white} Tabla de vectores liberada exitosamente. \n");
#endif
}
#endif

void free_all_vector()
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , free_all_vector)
            END_TYPE_FUNC_DBG
            );
    /*  Esta función se encarga de liberar los vectores almacenados en table_matriz_ */
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}free_all_vector#{FG:white}()\n");

    // Liberar los vectores almacenados en table_matriz_
    Node *current = table_matriz_->head;
    while (current != NULL && !empty(table_matriz_))
    {
        Node *next = current->next;
        LinkedList *vector = (LinkedList *)current->data;

        if (vector != NULL){
            #ifdef __VECTOR_LIST_DEBBUG__
                printLinkedList(vector);
            #endif
            if (deleteNodeID(vector, size_v(vector)-1) == -1) {
                freeLinkedList(vector);
                current->data = NULL;
            }
        }
        #ifdef __VECTOR_LIST_DEBBUG__
            printLinkedList(table_matriz_);
        #endif
        deleteNodeID(table_matriz_, size_v(table_matriz_)-1);
    }
#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}free_all_vector#{FG:red}] #{FG:white} vectores liberados. \n");
#endif
}

Node *get_node(LinkedList *list, const position pos)
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(Node * , get_node)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(const position, "pos = %d")
            END_TYPE_FUNC_DBG,
            list, pos);
    if (list == NULL || pos < 0)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}get_node#{FG:red}] #{FG:white} Lista invalida o posicion invalida \n");
        return NULL; // Lista inválida o posición inválida
    }

    Node *current = list->head;
    while (current != NULL && pos > 0)
    {
        current = current->next;
    }
    return current;
}

const position get_position(Node *node)
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , get_position)
                TYPE_DATA_DBG(Node *, "node = %p")
            END_TYPE_FUNC_DBG,
            node);
    if (node == NULL) return -1; // Nodo nulo, posición inválida
    return node->id;
}

LinkedList *createLinkedList()
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(LinkedList * , createLinkedList)
            END_TYPE_FUNC_DBG
            );

    // Crear una nueva lista enlazada
    // LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    LinkedList *list;
    debug_malloc(LinkedList, list, sizeof(LinkedList)); // Asignar memoria para la lista
    list->head = NULL;                                  // Establecer el puntero de inicio de la lista como nulo
    list->lastId = 0;                                   // Establecer la posición inicial en 0

    // Insertar una referencia de la lista en la tabla de registros
    insertNode(table_matriz_, list);
#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}createLinkedList#{FG:red}] #{FG:white} Registro de vectores reservados en run time (table_matriz_): \n");
    printLinkedList(table_matriz_);
#endif

    return list;
}

void *get_element_v(LinkedList *list, const position ID)
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void * , get_element_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(const position, "ID = %u")
            END_TYPE_FUNC_DBG,
            list, ID);

    // Buscar el elemento en la lista enlazada con el ID especificado
    if (list == NULL) return NULL;

    Node *current = list->head; // Obtener el primer nodo de la lista
    while (current != NULL)
    {
        if (current->id == ID)
        {
            // El ID coincide, devolver el puntero de datos del nodo actual
            DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_element_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}const position #{FG:white}ID#{FG:white}) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p\n;", current->data);
            return current->data;
        }
        current = current->next; // Avanzar al siguiente nodo
    }
    return NULL; // El ID no fue encontrado
}

void insertNode(LinkedList *list, void *data)
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void  , insertNode)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(void *, "data = %u")
            END_TYPE_FUNC_DBG,
            list, data);
    if (list == NULL || data == NULL) return;
    // Crear un nuevo nodo
    // Node *newNode = (Node *)malloc(sizeof(Node));
    Node *newNode;
    debug_malloc(Node, newNode, sizeof(Node));

    // Asignar un ID único al nodo
    newNode->id = list->lastId++;
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}insertNode#{FG:red}] #{FG:white}Data insert in node with ID: #{FG:lgreen}%zu#{FG:white}.\n", newNode->id);

    newNode->data = data; // Asignar el puntero de datos al nodo
    newNode->next = NULL; // Establecer el puntero next del nodo como NULL

    // Insertar el nodo en la lista enlazada
    if (list->head == NULL)
    {
        // Si la lista está vacía, el nuevo nodo se convierte en el primer nodo
        list->head = newNode;
    }
    else
    {
        // Si la lista no está vacía, encontrar el último nodo y enlazar el nuevo nodo a continuación
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
bool existsID(LinkedList *list, const position ID)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(bool  , existsID)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(const position, "ID = %u")
            END_TYPE_FUNC_DBG,
            list, ID);

    /*
     *
     *  Comprueba si existe una lista que tenga el ID especificado
     *
     */
    if (list == NULL) return false;

    Node *current = list->head; // Inicializar el puntero current al primer nodo de la lista
    while (current != NULL)     // Recorrer la lista para buscar el ID
    {
        // Comprobar si el ID del nodo actual coincide con el ID especificado
        if (current->id == ID)
        {
            // Si se encuentra el ID, retornar true
            return true;
        }
        current = current->next; // Avanzar al siguiente nodo
    }
    // Si no se encuentra el ID, retornar false
    return false;
}

bool exists(LinkedList *list, Node *node)
{
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(bool  , exists)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(Node *, "node = %p")
            END_TYPE_FUNC_DBG,
            list, node);

    if (list == NULL || node == NULL) return false;

    Node *current = list->head; // Inicializar el puntero current al primer nodo de la lista
    // Recorrer la lista para buscar el nodo
    while (current != NULL)
    {
        // Comprobar si el nodo actual es igual al nodo especificado
        if (node == NULL)
            break;
        if (current == node)
        {
            // Si se encuentra el nodo, retornar true
            DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred} bool#{FG:cyan} exists#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}Node #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}true\n");
            return true;
        }
        // Avanzar al siguiente nodo
        current = current->next;
    }
    // Si no se encuentra el nodo, retornar false
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}bool #{FG:cyan}exists#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}Node #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}false\n");
    return false;
}

void deleteNode(LinkedList *list, Node *node)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , deleteNode)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(Node *, "node = %p")
            END_TYPE_FUNC_DBG,
            list, node);

    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}deleteNode#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list = %p, #{FG:lyellow}Node* #{FG:white}node = %p#{FG:white})\n", list, node);
    // Comprobar si la lista o el nodo son nulos
    if (list == NULL || list->head == NULL || node == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNode#{FG:red}] #{FG:white} La lista o el nodo son nulos. \n");
        // Si la lista o el nodo son nulos, retornar sin hacer nada
        return;
    }

    // Comprobar si el nodo a eliminar es el primer nodo de la lista
    if (list->head == node)
    {
        // Actualizar el puntero head para eliminar el primer nodo
        list->head = list->head->next;
        // Liberar la memoria del nodo eliminado
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNode#{FG:red}] #{FG:white} nodo encontrado \n");
        free(node);
        // Actualizar los IDs de los nodos en la lista
        updateIds(list);
        return;
    }
    // Buscar el nodo a eliminar en la lista
    Node *prev = list->head;
    Node *current = list->head->next;

    while (current != NULL && current != node)
    {
        // Avanzar al siguiente nodo
        prev = current;
        current = current->next;
    }

    // Comprobar si se encontró el nodo a eliminar
    if (current != NULL)
    {
        // Conectar el nodo anterior con el siguiente nodo para eliminar el nodo actual
        prev->next = current->next;
        // Liberar la memoria del nodo eliminado
        free(current);
        // Actualizar los IDs de los nodos en la lista
        updateIds(list);
    }
    else
    {
        // Si el nodo no se encontró en la lista, mostrar un mensaje de error
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNode#{FG:red}] #{FG:white} El nodo no se encontro en la lista. \n");
    }
}

/*void deleteNodeID(LinkedList *list, const position ID)
{
    Node *current = list->head;
    Node *previous = NULL;
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}deleteNodeID#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list = %p, #{FG:lyellow}const position #{FG:white}ID = %zu#{FG:white})", list, ID);

    while (current != NULL)
    {
        printLinkedList(list);
        if (get_position(current) == ID)
        {
            if (previous != NULL)
            {
                previous->next = current->next;
            }
            else
            {
                list->head = current->next;
            }
            DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNodeID#{FG:red}] #{FG:white} ID: #{FG:lgreen}%zu#{FG:white}, encontrado ", ID);
            free(current);
            updateIds(list);
            return;
        }

        previous = current;
        current = current->next;
    }
}*/

int deleteNodeID(LinkedList *list, const position ID)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , deleteNodeID)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(const position, "ID = %u")
            END_TYPE_FUNC_DBG,
            list, ID);

    if (list == NULL || list->head == NULL)
    {
        #ifdef __VECTOR_LIST_DEBBUG__
                DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNodeID#{FG:red}] #{FG:white} La lista esta vacia.\n");
        #endif
        return -1;
    }

    // Comprobar si el nodo a eliminar es el primer nodo de la lista
    if (list->head->id == ID)
    {
        // Crear un nodo temporal para guardar el primer nodo
        Node *temp = list->head;
        // Actualizar el puntero head para eliminar el primer nodo
        list->head = list->head->next;
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNodeID#{FG:red}] #{FG:white} ID: #{FG:lgreen}%zu#{FG:white}, encontrado\n", ID);
        // free(temp->data);  // Liberar el contenido del nodo
        // Liberar la memoria del nodo eliminado
        free(temp);
        // Actualizar los IDs de los nodos en la lista
        updateIds(list);
        return 0;
    }

    // Buscar el nodo a eliminar en la lista
    Node *prev = list->head;
    Node *current = list->head->next;

    while (current != NULL && current->id != ID)
    {
        // Avanzar al siguiente nodo
        prev = current;
        current = current->next;
    }
    /*while (current != NULL && current->id != ID)
    {
        prev = current;
        current = current->next;
        if (current->id == ID)
            {
                Node *temp = current;
                current->head = list->head->next;
                DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNodeID#{FG:red}] #{FG:white} ID: #{FG:lgreen}%zu#{FG:white}, encontrado ", ID);
                // free(temp->data);  // Liberar el contenido del nodo
                free(temp);
                updateIds(list);
                return;
            }
    }*/
    // Comprobar si se encontró el nodo a eliminar
    if (current != NULL)
    {
        // Conectar el nodo anterior con el siguiente nodo para eliminar el nodo actual
        prev->next = current->next;
        // free(current->data);  // Liberar el contenido del nodo
        // Liberar la memoria del nodo eliminado
        free(current);
        // Actualizar los IDs de los nodos en la lista
        updateIds(list);
        return 0;
    }
    else
    {
        #ifdef __VECTOR_LIST_DEBBUG__
            DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}deleteNodeID#{FG:red}] #{FG:white} El nodo con ID #{FG:lgreen}%d#{FG:white} no se encontro en la lista.\n", ID);
        #endif
        return -1;
    }
}
void updateIds(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , updateIds)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return;

    // Establecer el primer nodo como el nodo actual
    Node *current = list->head;
    // Restablecer el valor de lastId a 0
    list->lastId = 0;
    // Recorrer todos los nodos de la lista
    while (current != NULL)
    {
        // Asignar el valor de lastId al ID del nodo actual
        current->id = list->lastId++;
        // Avanzar al siguiente nodo
        current = current->next;
    }
}

/*void updateIds(LinkedList *list)
{
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:cyan}deleteNodeID#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list = %p#{FG:white})", list);
    Node *current = list->head;
    position newId = 0;

    while (current != NULL)
    {
        current->id = newId;
        newId++;
        current = current->next;
    }

    list->lastId = newId - 1;
}*/

const position pop_back_v(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , pop_back_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    // Comprobar si la lista está vacía
    if (list == NULL || list->head == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}pop_back_v#{FG:red}] #{FG:white} La lista esta vacia.\n");
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
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}pop_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", id);
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
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}pop_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", id);
        // Retornar el ID del nodo eliminado
        return id;
    }
}

const position push_back_v(LinkedList *list, void *data)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , push_back_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
                TYPE_DATA_DBG(void *, "data = %p")
            END_TYPE_FUNC_DBG,
            list, data);

    // Comprobar si la lista o los datos son inválidos
    if (list == NULL || data == NULL)
    {
        // La lista es inválida o los datos no son válidos, retornar -1
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}push_back_v#{FG:red}] #{FG:white} La lista es invalida o data no es valido. \n");
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
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}push_back_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list, #{FG:lyellow}void* #{FG:white}node) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", newNode->id);
    // Retornar el ID del nuevo nodo agregado
    return newNode->id;
}

bool empty(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(bool , empty)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    // Comprobar si la lista es inválida
    if (list == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}bool #{FG:cyan}empty#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}false\n");
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}empty#{FG:red}] #{FG:white} La lista es invalida.\n");
        return false;
    }
    // Comprobar si la lista está vacía
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}bool #{FG:cyan}empty#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%s\n", list->head == NULL ? "false" : "true");
    return (list->head == NULL);
}

void clear(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
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

const position size_v(register LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , size_v)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    // Comprobar si la lista es inválida
    if (list == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}size_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}-1\n");
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}size_v#{FG:red}] #{FG:white} La lista es inválida. \n");
        return -1;
    }

    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}size_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list = %p)\n", list);
    register size_t count = 0;
    register Node *current = list->head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}size_v#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", count);
    return count;
}

void printLinkedList(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , printLinkedList)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}printLinkedList#{FG:red}] La lista no es valida#{FG:white} \n ");
        return;
    }
    Node *current = list->head;
    while (current != NULL)
    {
        printf_color("#{FG:red}%zu ", current->id); // Imprimir el ID del nodo
        current = current->next;
    }
    printf_color("\n");
}

void freeLinkedList(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void , freeLinkedList)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

#ifdef __VECTOR_LIST_DEBBUG__
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}freeLinkedList#{FG:red}] #{FG:white} Registro de vectores reservados en run time (table_matriz_): \n");
    printLinkedList(table_matriz_);
#endif

    if (list == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}freeLinkedList#{FG:red}] #{FG:white} Lista invalida \n");
        return;
    }

    Node *current = list->head;
    while (current != NULL)
    {
#ifdef __VECTOR_LIST_DEBBUG__
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}freeLinkedList#{FG:red}] #{FG:white} freeLinkedList: %zu\n ", current->id);
#endif
        Node *temp = current;
        current = current->next;
        // temp->data = NULL;
        // temp->next = NULL;
        deleteNodeID(table_matriz_, temp->id); // Eliminar el nodo de table_matriz_
        free(temp);
    }
    // free(list);
    list = NULL;
}
Node *get_last_node(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(Node * , get_last_node)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL || list->head == NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:red}[#{FG:yellow}get_last_node#{FG:red}] #{FG:white}Lista vacia\n");
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}Node #{FG:white}*#{FG:cyan}get_last_node#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", NULL);
        return NULL; // Lista vacía
    }

    Node *current = list->head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}Node #{FG:white}*#{FG:cyan}get_last_node#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", current);
    return current;
}

void *get_last(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(void * , get_last)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return NULL;
    Node *lastNode = get_last_node(list);
    if (lastNode != NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", lastNode->data);
        return lastNode->data;
    }
    else
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}void #{FG:white}*#{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%p;\n", NULL);
        return NULL;
    }
}

const position get_last_position(LinkedList *list)
{

        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO,
            INIT_TYPE_FUNC_DBG(const position , get_last_position)
                TYPE_DATA_DBG(LinkedList *, "list = %p")
            END_TYPE_FUNC_DBG,
            list);

    if (list == NULL) return 0;
    Node *lastNode = get_last_node(list);
    if (lastNode != NULL)
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%zu;\n", lastNode->id);
        return lastNode->id;
    }
    else
    {
        DEBUG_PRINT_VECTOR_LIST(DEBUG_LEVEL_INFO, "#{FG:lred}const position #{FG:cyan}get_last#{FG:white}(#{FG:lyellow}LinkedList  #{FG:white}*list) #{FG:lred}-> #{FG:lgreen}return #{FG:white}%zu;\n", -1);
        return -1; // Lista vacía
    }
}

#endif
