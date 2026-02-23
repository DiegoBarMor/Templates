#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

name_project=$(basename "$(realpath .)")

mkdir -p build
while IFS= read -r -d '' path_c; do
    stem="$(basename -s ".c" "$path_c")"
    path_o="build/$stem.o"
    # shellcheck disable=SC2046
    clang -Iinclude $(pkg-config --cflags raylib) -c "$path_c" -o "$path_o"
done <   <(find src -name '*.c' -print0)

# shellcheck disable=SC2046
clang build/*.o -o "$name_project" $(pkg-config --libs raylib) -lm -lpthread -ldl -lrt -lX11
