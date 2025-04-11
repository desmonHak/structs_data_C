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
void postorder_ast(ast_t* node, void (*op)(ast_t*)) {
    // Caso base: nodo nulo o función no proporcionada
    if (node == NULL || op == NULL) return;
    
    // Recorrer todas las ramas (hijos) del nodo actual
    for (size_t i = 0; i < size_a(node->ramas); i++) {
        // Obtener el hijo actual del ArrayList de ramas
        ast_t* child = (ast_t*)get_element_a(node->ramas, i);
        
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
    if (node == NULL) return NULL;

    ast_node_t* newNode = create_ast_node_t(node->data);
    for (size_t i = 0; i < size_a(node->ramas); i++) {
        ast_node_t* child = get_element_a(node->ramas, i);
        push_back_a(newNode->ramas, clone_ast(child));
    }

    return newNode;
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
void free_ast_t(ast_t* ast, void (*free_f)(void*)) {
    if (ast == NULL) return;
    
    // Variable estática para pasar free_f al callback (no thread-safe)
    static void (*current_free)(void*) = NULL;
    current_free = free_f;
    
    // Función interna para liberar cada nodo en postorden
    void postorder_free(ast_t* node) {
        // 1. Liberar datos del nodo si existe la función
        if (current_free != NULL && node->data != NULL) {
            current_free(node->data);
        }
        
        // 2. Finalmente liberar el nodo mismo
        free(node);
    }
    
    // Recorrer el árbol en postorden aplicando la liberación
    postorder_ast(ast, postorder_free);
    
    current_free = NULL; // Resetear para siguiente uso
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
void inorder_ast(ast_t *node, void (*op)(ast_t *))
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
    if (parent == NULL) return NULL;

    ast_t* child = create_ast_node_t(data);
    if (child == NULL) return NULL;

    push_back_a(parent->ramas, child);
    return child;
}


#endif