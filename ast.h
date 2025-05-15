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

#ifndef __AST_H__
#define __AST_H__

#include "array-list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "debug_c.h"

/**
 * @brief Nodos para el AST y el nodo padre
 * 
 */
typedef struct ast_node_t {
    void        *data;
    ArrayList   *ramas;
} ast_node_t, ast_t;

ast_t* create_ast_t(void *data);
ast_node_t* create_ast_node_t(void *data);
ast_t* clone_ast(ast_t* node);
ast_t* add_child(ast_t* parent, void* data);
void free_ast_t(const ast_t* ast, void (*free_f)(void*));
void inorder_ast(const ast_t *node, void (*op)(const ast_t *));
void postorder_ast(const ast_t* node, void (*op)(const ast_t*));
void preorder_ast(const ast_t* node, void (*op)(const ast_t*));
void print_ast_normal_order(ast_t* ast);
void print_ast_ascii(ast_t* node, char* prefix, int is_last);
void print_ast(
    ast_t* ast, 
    void (*traversal_func)(
        ast_t*, 
        void (*op)(
            ast_t*, 
            int, 
            char*, 
            int
        ), 
        int, 
        char*, 
        int
    )
);
void inorder_ast_with_ascii(
    ast_t* node, 
    void (*op)(ast_t*, int, char*, int), 
    int depth, 
    char* prefix, 
    int is_last
);
void postorder_ast_with_ascii(
    ast_t* node, 
    void (*op)(ast_t*, int, char*, int), 
    int depth, 
    char* prefix, 
    int is_last
);
void preorder_ast_with_ascii(
    ast_t* node, 
    void (*op)(ast_t*, int, char*, int), 
    int depth, 
    char* prefix, 
    int is_last
);
ast_t* search_node_by_route(
    const char* path, 
    ast_t* root, 
    char* (*how_get_str)(ast_t*)
);

#endif