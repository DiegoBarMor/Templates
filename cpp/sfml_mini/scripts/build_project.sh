#!/bin/bash
set -euo pipefail

### Compile and link the project source files
### Simplified build assumes a single "main.cpp" file and no "src" or "include" directories.
### Last updated: 2026/08/03

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

compile_mini() {
    mkdir -p build
    # shellcheck disable=SC2046
    g++ -c main.cpp $(pkg-config --cflags sfml-all) -o build/main.o
}
link_mini() {
    ### the files in SFML/tools/pkg-config specify the library names without the -s "suffix"
    ### however, during installation, the libraries are named with the -s suffix (e.g. "libsfml-graphics-s.a" instead of "libsfml-graphics.a")
    ### the lines below are a workaround to fix this issue
    local sfml_libs
    sfml_libs=$(pkg-config --static --libs sfml-all)
    sfml_libs=${sfml_libs//-lsfml-graphics/-lsfml-graphics-s}
    sfml_libs=${sfml_libs//-lsfml-window/-lsfml-window-s}
    sfml_libs=${sfml_libs//-lsfml-audio/-lsfml-audio-s}
    sfml_libs=${sfml_libs//-lsfml-network/-lsfml-network-s}
    sfml_libs=${sfml_libs//-lsfml-system/-lsfml-system-s}

    # shellcheck disable=SC2086
    g++ build/main.o -o build/main $sfml_libs -lX11 -lXrandr -lXi -lXcursor -ludev -ldl -pthread -lfreetype -lharfbuzz
}

compile_mini
link_mini
