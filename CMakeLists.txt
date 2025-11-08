cmake_minimum_required(VERSION 3.15)
project(graph_project C)
set(CMAKE_BUILD_TYPE Debug)
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

# Debug flags: symbols, warnings, sanitizers
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer")

add_executable(graphs main.c)

# Link against igraph + sanitizers
target_link_libraries(graphs igraph)
