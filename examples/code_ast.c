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

#include "ast.h"

void print_data_node(const ast_t* node) {
    if (node == NULL) {
        return;
    }
    printf("node %s\n", (const char*)node->data);
}
char* get_node_name(const ast_t* node) {
    if (node && node->data)
        return (char*)node->data;
    return nullptr;
}
int main() {
    #ifdef _WIN32
        #include <windows.h>
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    // Crear el nodo raíz
    ast_t* root = create_ast_t("root");

    // Añadir hijos al nodo raíz
    ast_t* child1 = add_child(root, "child1");
    ast_t* child2 = add_child(root, "child2");
    ast_t* child3 = add_child(root, "child3");
    (void)child3; // var no usada, solo ejemplo

    // Añadir subhijos a uno de los hijos
    add_child(child1, "child1.1");
    add_child(child1, "child1.2");

    add_child(child2, "child2.1");

    print_ast_normal_order(root);

    printf("Recorrido Postorder del AST:\n");
    print_ast(root, postorder_ast_with_ascii);
    postorder_ast(root, print_data_node);

    printf("Recorrido Inorden del AST:\n");
    print_ast(root, inorder_ast_with_ascii);
    inorder_ast(root, print_data_node);

    printf("Recorrido Preorder del AST:\n");
    print_ast(root, preorder_ast_with_ascii);
    preorder_ast(root, print_data_node);


    
    // Buscar un nodo por ruta
    ast_t* found_node = search_node_by_route("root/child1/child1.1", root, (char * (*)(ast_t *))get_node_name);
    // Imprimir el resultado
    if (found_node != NULL) {
        printf("Found node: %s\n", get_node_name(found_node));
    } else {
        printf("Node not found\n");
    }

    //freeArrayList(&(child1->ramas));
    //freeArrayList(&(child2->ramas));
    //freeArrayList(&(child3->ramas));

    //free(child1);
    //free(child2);
    //free(child3);

    // no es necesario una subrutina de liberacion por que no se uso memoria dinamica
    free_ast_t(root, nullptr);



    puts("Exit...");
    return 0;
}