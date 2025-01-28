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

#ifndef __MATRIZ_LIST_H__
#define __MATRIZ_LIST_H__

#include "./DebugLibC/debug_c.h"
#include "array-list.h"
#include <stdarg.h>
#include <math.h>

typedef struct Matriz {
    ArrayList *list;
    ArrayList *dimensiones_matriz;
} Matriz;

typedef position dimensiones;

Matriz* createMatriz(dimensiones dimensionesMatriz, ...);
Matriz* newMatriz();
Matriz* freeMatriz(Matriz* matriz);
void createColumns(Matriz* matriz, position columns);
void createRow(Matriz* matriz, position row);
dimensiones get_size_va_list(dimensiones dimensionesMatriz, va_list args);
dimensiones get_size_size_total(dimensiones dimensionesMatriz, ...);
ArrayList* dimensiones_matriz(dimensiones dimensionesMatriz, ...);
ArrayList* dimensiones_matriz_va_list(dimensiones dimensionesMatriz, va_list args);

#ifdef INCLUDE_COLORS_C
#include "matriz-list.c"
#endif
#endif