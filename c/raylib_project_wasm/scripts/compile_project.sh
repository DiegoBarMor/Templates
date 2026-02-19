#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

name_project=$(basename "$(realpath .)")

mkdir -p build
for path_c in src/*; do
    stem="$(basename -s ".c" "$path_c")"
    # echo $path_c $stem
    path_o="build/$stem.o"
    # shellcheck disable=SC2046
    clang -Iinclude $(pkg-config --cflags raylib) -c "$path_c" -o "$path_o"
done
# shellcheck disable=SC2046
clang build/*.o -o "$name_project" $(pkg-config --libs raylib) -lm -lpthread -ldl -lrt -lX11
