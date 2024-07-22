cmake_minimum_required(VERSION 3.20.0)
project(pafl)

# Flag
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source
file(GLOB_RECURSE SOURCES
    src/*.cpp
    include/stmt_graph/*.cpp
    )
message(src)

# External source
file(GLOB_RECURSE TREE_SITTER_SRC
    externals/tree-sitter/lib/src/lib.c
    externals/tree-sitter-cpp/src/*.c
    externals/tree-sitter-python/src/*.c
    )

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${TREE_SITTER_SRC}
    )

# Include
include_directories(
    include
    )

# Externals
include_directories(
    externals
    externals/tree-sitter/lib/include
    externals/tree-sitter-cpp/bindings/c
    externals/tree-sitter-python/bindings/c
    )
