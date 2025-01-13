CC 			  = gcc
ARR			  = ar

VESRION_C     = 11

PATH_SRC 	      = src
PATH_INCLUDE      = include
PATH_EXAMPLES	  = example
PATH_DEBUG 		  = DebugLibC
PATH_COLORS		  = $(PATH_DEBUG)/colors-C-C-plus-plus

LINKER_FLAGS  	  =  -L. -lstructs_data_c -L$(PATH_DEBUG) -ldebug -L$(PATH_COLORS) -lcolors

INCLUDE_FLAGS = -I. -I$(PATH_DEBUG) -I$(PATH_COLORS)
GLOBAL_CFLAGS = -std=c$(VESRION_C) $(INCLUDE_FLAGS) -masm=intel \
				-D_ExceptionHandler -fdiagnostics-color=always

CFLAGS 		  =  $(GLOBAL_CFLAGS) -O3 -Wno-unused-parameter \
				-Wno-implicit-fallthrough -Wno-type-limits  \
				-Wno-unused-variable -Wno-pointer-sign
ARR_FLAGS     = -rc

CFLAGS_EXAMPLES = $(CFLAGS) -x c  -time  -save-temps -g -D DEBUG_ENABLE $(LINKER_FLAGS)

OBJECTS 	  = array-list.o hash-table.o matriz-list.o vector-list.o