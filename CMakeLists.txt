cmake_minimum_required(VERSION 3.15)
project(graph_project C)

set(CMAKE_C_STANDARD 11)

# Generate compile_commands.json for Neovim LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Homebrew install path for libs
set(HOMEBREW_PREFIX "/opt/homebrew")

include_directories(
    ${HOMEBREW_PREFIX}/include
    ${HOMEBREW_PREFIX}/include/igraph
)

link_directories(${HOMEBREW_PREFIX}/lib)

add_executable(graphs main.c)

# Link against igraph
target_link_libraries(graphs igraph)
