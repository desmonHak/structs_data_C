cmake_minimum_required(VERSION 3.31)
project(structs_data_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(CIterators)
include_directories(CIterators/examples)
include_directories(CIterators/include)
include_directories(CIterators/src)
include_directories(DebugLibC)
include_directories(DebugLibC/colors-C-C-plus-plus)
include_directories(src)

# examples/code_array-list_vector-list.c

add_executable(code_array-list_vector-list
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_array-list_vector-list.c)


# examples/code_ast.c

add_executable(code_ast
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_ast.c)


# examples/code_hash-table.c

add_executable(code_hash-table
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_hash-table.c)


# examples/code_matriz-list.c

add_executable(code_matriz-list
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_matriz-list.c)


# examples/code_vector-list.c
add_executable(code_vector-list
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_vector-list.c)

# examples/code_array-list.c
add_executable(code_array-list
        CIterators/include/CIterators.h
        CIterators/include/CSortting.h
        CIterators/src/CIterators.c
        CIterators/src/CSortting.c
        DebugLibC/colors-C-C-plus-plus/src/colors.c
        DebugLibC/colors-C-C-plus-plus/colors.h
        DebugLibC/src/debug_c.c
        DebugLibC/src/error_c.c
        DebugLibC/src/time_code.c
        DebugLibC/debug_c.h
        DebugLibC/error_c.h
        DebugLibC/time_code.h
        src/array-list.c
        src/ast.c
        src/hash-table.c
        src/matriz-list.c
        src/vector-list.c
        array-list.h
        ast.h
        hash-table.h
        matriz-list.h
        vector-list.h
        examples/code_array-list.c)
