#!/bin/bash
set -euo pipefail

### Compile and link the project source files
### Simplified build assumes a single "main.c" file and no "src" or "include" directories.
### Last updated: 2026/08/03

if [ ! -f "main.c" ]; then
    echo "Error: script must be run in the project folder containing the 'main.c' file."
    exit 1
fi

compile_mini() {
    mkdir -p build
    # shellcheck disable=SC2046
    clang -Iinclude $(pkg-config --cflags raylib) -c "main.c" -o "main.o"
}
link_mini() {
    local name_project
    name_project=$(basename "$(realpath .)")
    # shellcheck disable=SC2046
    clang main.o -o "$name_project" $(pkg-config --libs raylib) -lm -lpthread -ldl -lrt -lX11
}

compile_mini
link_mini
