CC 			  = gcc
ARR			  = ar

VESRION_C     =11

PATH_SRC 	      = src
PATH_INCLUDE      = include
PATH_EXAMPLES	  = examples
PATH_DEBUG 		  = DebugLibC
PATH_COLORS		  = $(PATH_DEBUG)/colors-C-C-plus-plus

LINKER_FLAGS  	  =  -L. -lstructs_data_c -L$(PATH_DEBUG) -ldebug -L$(PATH_COLORS) -lcolors

INCLUDE_FLAGS = -I. -I$(PATH_DEBUG) -I$(PATH_COLORS)
GLOBAL_CFLAGS = -std=c$(VESRION_C) $(INCLUDE_FLAGS) -masm=intel \
				-D_ExceptionHandler -fdiagnostics-color=always -D_GNU_SOURCE $(DEBUG_LINUX)
				
ifeq ($(OS_NAME),windows)
else
	GLOBAL_CFLAGS += -fPIC -D_GNU_SOURCE  -D_POSIX_C_SOURCE=200809L
endif

CFLAGS 		  =  $(GLOBAL_CFLAGS) -O3 -Wno-unused-parameter \
				-Wno-implicit-fallthrough -Wno-type-limits  \
				-Wno-unused-variable -Wno-pointer-sign 
CFLAGS_DEBUG  =  $(GLOBAL_CFLAGS) -ggdb -fno-asynchronous-unwind-tables  	    	\
				-Wall -Wextra -pipe -O0 -D DEBUG_ENABLE      	          			\
				-fstack-protector-strong -Wpedantic -fno-omit-frame-pointer       	\
				-fno-inline -fno-optimize-sibling-calls -fdiagnostics-show-option 	\
				-fPIC -DDEBUG_VECTOR_LIST

ARR_FLAGS     = -rc

CFLAGS_EXAMPLES = $(CFLAGS) -x c  -time  -save-temps -g -D DEBUG_ENABLE $(LINKER_FLAGS)

OBJECTS 	  = array-list.o hash-table.o matriz-list.o vector-list.o ast.o hash-table-dynamic.o
OBJECTS_DEBUG = array-list_debug.o hash-table_debug.o matriz-list_debug.o \
	vector-list_debug.o ast_debug.o hash-table-dynamic_debug.o