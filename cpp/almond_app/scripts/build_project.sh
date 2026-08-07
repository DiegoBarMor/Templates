#!/bin/bash
set -euo pipefail

### Compile and link the project source files (without CMake)
### Must run "scripts/install_sfml.sh" at some point first (once).
### Simplified build assumes a single "main.cpp" file and no "src" or "include" directories.
### Last updated: 2026/08/07

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

if [ ! -f "almond.hpp" ]; then
    ftmp=$(mktemp -d)
    git clone --depth 1 --branch main https://github.com/DiegoBarMor/almond "$ftmp"
    cd "$ftmp"
    bash scripts/pack_header/run.sh # generates "almond.hpp"
    cd - >/dev/null
    mv "$ftmp/almond.hpp" almond.hpp
fi

sfml_flags() {
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
    echo $sfml_libs -lX11 -lXrandr -lXi -lXcursor -ludev -ldl -pthread -lfreetype -lharfbuzz
}
compile_mini() { ### use for "mini" projects
    mkdir -p build
    # shellcheck disable=SC2046
    g++ -c main.cpp $(pkg-config --cflags sfml-all) -o build/main.o
}
link_mini() { ### use for "mini" projects
    # shellcheck disable=SC2046
    g++ build/main.o -o build/main $(sfml_flags)
}
compile_modular() { ### use for "modular" projects
    local path_src=$1
    local path_build=$2

    while IFS= read -r -d '' path_cpp; do
        stem="$(basename -s ".cpp" "$path_cpp")"
        path_o="$path_build/$stem.o"
        # shellcheck disable=SC2046
        g++ -c "$path_cpp" $(pkg-config --cflags sfml-all) -o "$path_o"
    done <   <(find "$path_src" -name '*.cpp' -print0)
}
link_modular() { ### use for "modular" projects
    local path_build=$1
    # shellcheck disable=SC2046
    g++ "$path_build"/*.o -o "$path_build/app" $(sfml_flags)
}

compile_mini # mini or modular, as needed
link_mini
