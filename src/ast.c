#ifndef __AST_C__
#define __AST_C__

#include "ast.h"

/**
 * @brief Create un nodo ast
 * 
 * @param data datos a guardar en el nuevo nodo
 * @param id ID virtual para el nodo creado.
 * @return ast_node_t* nodo nuevo creado con los datos indicados
 */
ast_node_t* create_ast_node_t(void *data) {
    ast_node_t* node = (ast_node_t*)malloc(sizeof(ast_node_t));
    if (!node) {
        perror("Failed to allocate memory for ASTNode");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->ramas = createArrayList(0, NULL);
    return node;
}

/**
 * @brief Crea el nodo padre
 * 
 * @param data datos que incluir en el nodo padre, NULL si no se requiere
 * @return ast_t* nodo padre de todo el AST
 */
ast_t* create_ast_t(void *data) {
    ast_t* root = create_ast_node_t(data);
    return root;
}

/**
 * @brief Recorre un árbol AST en postorden (hijos primero, luego nodo padre)
 * 
 * @param node Nodo raíz del árbol/subárbol a recorrer
 * @param op Función callback a aplicar en cada nodo durante el recorrido
 */
void postorder_ast(const ast_t* node, void (*op)(const ast_t*)) {
    // Caso base: nodo nulo o función no proporcionada
    if (node == NULL || op == NULL) return;
    
    // Recorrer todas las ramas (hijos) del nodo actual
    for (size_t i = 0; i < size_a(node->ramas); i++) {
        // Obtener el hijo actual del ArrayList de ramas
        const ast_t* child = (ast_t*)get_element_a(node->ramas, i);
        
        // Llamada recursiva para procesar el subárbol del hijo
        postorder_ast(child, op);
    }
    
    // Aplicar la operación al nodo actual después de procesar todos los hijos
    op(node);
}


/**
 * @brief Permite copiar una rama o arbol con sus subnodos.
 * 
 * @param node nodo padre de un arbol o un nodo del cual hacer una copia
 * junto a sus subnodos
 * @return ast_t* copia de ast.
 */
ast_t* clone_ast(ast_t* node) {
    if (node == NULL) return nullptr;

    ast_node_t* newNode = create_ast_node_t(node->data);
    for (size_t i = 0; i < size_a(node->ramas); i++) {
        ast_node_t* child = get_element_a(node->ramas, i);
        push_back_a(newNode->ramas, clone_ast(child));
    }

    return newNode;
}

// Variable estática para pasar free_f al callback (no thread-safe)
static void (*current_free)(void*) = nullptr;

// Función interna para liberar cada nodo en postorden
void postorder_free(ast_t* node) {
    // 1. Liberar datos del nodo si existe la función
    if (current_free != NULL && node->data != NULL) {
        current_free(node->data);
    }

    // 2. Finalmente liberar el nodo mismo
    free(node);
}
/**
 * @brief Permite liberar un nodo con sus subnodos o todo un árbol.
 * 
 * Usa un recorrido postorder (hijos primero, luego padre) para liberar
 * de forma segura toda la memoria asociada al árbol.
 * 
 * @param ast Árbol o nodo a liberar.
 * @param free_f Función para liberar los datos contenidos en cada nodo.
 */
void free_ast_t(const ast_t* ast, void (*free_f)(void*)) {
    if (ast == NULL) return;
    // Variable estática para pasar free_f al callback (no thread-safe)
    current_free = free_f;

    // Recorrer el árbol en postorden aplicando la liberación
    postorder_ast(ast, (void (*)(const ast_t*))postorder_free);
    
    current_free = nullptr; // Resetear para siguiente uso
}


/**
 * @brief Recorre un árbol AST en preorden (nodo padre primero, luego hijos) aplicando una función callback.
 *
 * La estrategia consiste en aplicar la operación sobre el dato del nodo actual,
 * y luego recorrer todas las ramas del nodo.
 *
 * @param node Nodo raíz del árbol/subárbol a recorrer.
 * @param op Función callback a aplicar en cada nodo durante el recorrido.
 */
void preorder_ast(const ast_t* node, void (*op)(const ast_t*)) {
    if (node == NULL || op == NULL) return;

    // Aplicar la operación al nodo actual
    op(node);

    // Recorrer todas las ramas (hijos)
    size_t num_ramas = size_a(node->ramas);
    for (size_t i = 0; i < num_ramas; i++) {
        const ast_t* child = (ast_t*)get_element_a(node->ramas, i);

        // Llamada recursiva para procesar los hijos
        preorder_ast(child, op);
    }
}

/**
 * @brief Recorre en inorden un árbol AST (n-ario) aplicando la función op a cada dato.
 *
 * La estrategia consiste en recorrer primero la mitad de las ramas del nodo, 
 * luego aplicar la operación sobre el dato del nodo actual, y finalmente 
 * recorrer el resto de las ramas.
 *
 * @param node Puntero al nodo AST a recorrer.
 * @param op Función a aplicar a cada dato almacenado en el nodo.
 */
void inorder_ast(const ast_t *node, void (*op)(const ast_t *))
{
    if (node == NULL || op == NULL)
        return;
        
    // Obtiene el número de ramas usando la función del ArrayList
    size_t n = size_a(node->ramas);
    size_t mid = n / 2;  // División entera para determinar el punto medio

    // Recorre las ramas de la primera mitad
    for (size_t i = 0; i < mid; i++) {
        // Se asume que get_element_a devuelve un puntero a ast_t*
        ast_t *child = (ast_t *)get_element_a(node->ramas, i);
        inorder_ast(child, op);
    }
    
    // Aplica la operación al dato contenido en el nodo actual
    op(node);
    
    // Recorre las ramas de la segunda mitad
    for (size_t i = mid; i < n; i++) {
        ast_t *child = (ast_t *)get_element_a(node->ramas, i);
        inorder_ast(child, op);
    }
}

/**
 * @brief Añade un nuevo nodo hijo a un nodo existente en el árbol AST.
 *
 * @param parent Puntero al nodo padre al que se añadirá el nuevo hijo.
 * @param data Puntero a los datos que se almacenarán en el nuevo nodo hijo.
 * @return ast_t* Puntero al nuevo nodo hijo creado, o NULL si ocurre un error.
 */
ast_t* add_child(ast_t* parent, void* data) {
    if (parent == NULL) return nullptr;

    ast_t* child = create_ast_node_t(data);

    push_back_a(parent->ramas, child);
    return child;
}

/**
 * @brief Imprime un árbol AST utilizando arte ASCII para representar la estructura.
 * 
 * @param node Nodo raíz del árbol/subárbol a imprimir.
 * @param prefix Prefijo utilizado para construir la estructura ASCII.
 * @param is_last Indica si el nodo actual es el último hijo.
 */
void print_ast_ascii(ast_t* node, char* prefix, int is_last) {
    if (node == NULL) return;

    // Imprimir el nodo actual con arte ASCII
    printf("%s%s%s\n", prefix, is_last ? "└── " : "├── ", (char*)node->data);

    // Actualizar el prefijo para los hijos
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

    // Recorrer las ramas (hijos) del nodo actual
    size_t num_ramas = size_a(node->ramas);
    for (size_t i = 0; i < num_ramas; i++) {
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);
        print_ast_ascii(child, new_prefix, i == num_ramas - 1);
    }
}


/**
 * @brief Wrapper para imprimir un árbol AST completo con arte ASCII.
 * 
 * @param ast Árbol AST a imprimir.
 */
void print_ast_normal_order(ast_t* ast) {
    if (ast == NULL) {
        printf("Error: AST is empty\n");
        return;
    }

    printf("AST Structure:\n");
    print_ast_ascii(ast, "", 1);
}


/**
 * @brief Recorre un árbol AST en inorden (n-ario) aplicando una función callback.
 *
 * La estrategia consiste en recorrer primero la mitad de las ramas del nodo,
 * luego aplicar la operación sobre el dato del nodo actual, y finalmente
 * recorrer el resto de las ramas.
 *
 * @param node Nodo raíz del árbol/subárbol a recorrer.
 * @param op Función callback a aplicar en cada nodo durante el recorrido.
 * @param depth Profundidad actual del nodo (para arte ASCII).
 * @param prefix Prefijo utilizado para construir la estructura ASCII.
 * @param is_last Indica si el nodo actual es el último hijo.
 */
void inorder_ast_with_ascii(ast_t* node, void (*op)(ast_t*, int, char*, int), int depth, char* prefix, int is_last) {
    if (node == NULL || op == NULL) return;

    // Obtener número de ramas
    size_t num_ramas = size_a(node->ramas);
    size_t mid = num_ramas / 2;

    // Recorrer la primera mitad de las ramas
    for (size_t i = 0; i < mid; i++) {
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);

        // Actualizar el prefijo para los hijos
        char new_prefix[256];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

        inorder_ast_with_ascii(child, op, depth + 1, new_prefix, i == num_ramas - 1);
    }

    // Aplicar la operación al nodo actual
    op(node, depth, prefix, is_last);

    // Recorrer la segunda mitad de las ramas
    for (size_t i = mid; i < num_ramas; i++) {
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);

        // Actualizar el prefijo para los hijos
        char new_prefix[256];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

        inorder_ast_with_ascii(child, op, depth + 1, new_prefix, i == num_ramas - 1);
    }
}

/**
 * @brief Recorre un árbol AST en postorden (n-ario) aplicando una función callback.
 *
 * La estrategia consiste en recorrer primero todas las ramas del nodo,
 * y luego aplicar la operación sobre el dato del nodo actual.
 *
 * @param node Nodo raíz del árbol/subárbol a recorrer.
 * @param op Función callback a aplicar en cada nodo durante el recorrido.
 * @param depth Profundidad actual del nodo (para arte ASCII).
 * @param prefix Prefijo utilizado para construir la estructura ASCII.
 * @param is_last Indica si el nodo actual es el último hijo.
 */
void postorder_ast_with_ascii(ast_t* node, void (*op)(ast_t*, int, char*, int), int depth, char* prefix, int is_last) {
    if (node == NULL || op == NULL) return;

    // Recorrer todas las ramas (hijos)
    size_t num_ramas = size_a(node->ramas);
    for (size_t i = 0; i < num_ramas; i++) {
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);

        // Actualizar el prefijo para los hijos
        char new_prefix[256];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

        // Llamada recursiva para procesar los hijos
        postorder_ast_with_ascii(child, op, depth + 1, new_prefix, i == num_ramas - 1);
    }

    // Aplicar la operación al nodo actual después de procesar los hijos
    op(node, depth, prefix, is_last);
}

/**
 * @brief Recorre un árbol AST en preorden (n-ario) aplicando una función callback.
 *
 * La estrategia consiste en aplicar la operación sobre el dato del nodo actual,
 * y luego recorrer todas las ramas del nodo.
 *
 * @param node Nodo raíz del árbol/subárbol a recorrer.
 * @param op Función callback a aplicar en cada nodo durante el recorrido.
 * @param depth Profundidad actual del nodo (para arte ASCII).
 * @param prefix Prefijo utilizado para construir la estructura ASCII.
 * @param is_last Indica si el nodo actual es el último hijo.
 */
void preorder_ast_with_ascii(ast_t* node, void (*op)(ast_t*, int, char*, int), int depth, char* prefix, int is_last) {
    if (node == NULL || op == NULL) return;

    // Aplicar la operación al nodo actual
    op(node, depth, prefix, is_last);

    // Recorrer todas las ramas (hijos)
    size_t num_ramas = size_a(node->ramas);
    for (size_t i = 0; i < num_ramas; i++) {
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);

        // Calcular el nuevo prefijo para los hijos
        char new_prefix[256];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

        // Llamada recursiva para procesar los hijos
        preorder_ast_with_ascii(child, op, depth + 1, new_prefix, i == num_ramas - 1);
    }
}


static void print_node(ast_t* node, int depth, char* prefix, int is_last) {
    printf("%s%s%s\n", prefix, is_last ? "└── " : "├── ", (char*)node->data);
}
/**
 * @brief Imprime un árbol AST utilizando arte ASCII con un recorrido personalizado.
 * 
 * Permite especificar una función de recorrido (postorden, inorden, etc.)
 * para personalizar el orden en que los nodos son visitados.
 * 
 * @param ast Árbol AST a imprimir.
 * @param traversal_func Función de recorrido a aplicar (postorder_ast, inorder_ast, etc.).
 */
void print_ast(ast_t* ast, void (*traversal_func)(ast_t*, void (*op)(ast_t*, int, char*, int), int, char*, int)) {
    if (ast == NULL) {
        printf("Error: AST is empty\n");
        return;
    }

    printf("AST Structure:\n");

    // Función interna para imprimir un nodo con formato ASCII


    // Llamar a la función de recorrido con la función interna
    traversal_func(ast, print_node, 0, "", 1);
}


/**
 * @brief Busca un nodo en el árbol AST por una ruta dada.
 * 
 * @param path Ruta del nodo a buscar (ej: "hola/que/tal").
 * @param root Nodo raíz del árbol.
 * @param how_get_str Función para obtener el string de un nodo.
 * @return ast_t* Puntero al nodo encontrado, o NULL si no se encuentra.
 */
/**
 * @brief Busca un nodo en el árbol AST por una ruta dada.
 * 
 * @param path Ruta del nodo a buscar (ej: "root/child1/child1.1").
 * @param root Nodo raíz del árbol.
 * @param how_get_str Función para obtener el string de un nodo.
 * @return ast_t* Puntero al nodo encontrado, o NULL si no se encuentra.
 */
ast_t* search_node_by_route(
    const char* path, 
    ast_t* root, 
    char* (*how_get_str)(ast_t*)
) {
    if (path == NULL || root == NULL || how_get_str == NULL) {
        return nullptr;
    }

    // Duplicar la ruta para poder modificarla con strtok
    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("Failed to allocate memory for path copy");
        return nullptr;
    }

    // Obtener el primer token (componente de la ruta)
    char *token = strtok(path_copy, "/");
    ast_t* current_node = root;

    // Comprobar si el primer token coincide con el nombre del nodo raíz
    if (token == NULL || strcmp(token, how_get_str(root)) != 0) {
        free(path_copy);
        return NULL;
    }

    // Recorrer la ruta, comenzando desde el segundo token
    token = strtok(nullptr, "/");
    while (token != NULL && current_node != NULL) {
        int found = 0;
        // Recorrer las ramas del nodo actual
        for (size_t i = 0; i < size_a(current_node->ramas); i++) {
            ast_t* child = (ast_t*)get_element_a(current_node->ramas, i);
            
            // Comparar el nombre del nodo hijo con el token actual
            if (strcmp(token, how_get_str(child)) == 0) {
                current_node = child;
                found = 1;
                break;
            }
        }

        // Si no se encuentra el token en las ramas, la ruta es inválida
        if (!found) {
            free(path_copy);
            return nullptr;
        }

        // Obtener el siguiente token
        token = strtok(nullptr, "/");
    }

    // Liberar la copia de la ruta
    free(path_copy);

    // Si `token` es NULL, significa que hemos recorrido toda la ruta
    // y el nodo actual es el que buscábamos
    return current_node;
}


#endif