#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

###### options for NAME_MINSHELL
### minshell           -> plain canvas
### minshell_chocomint -> canvas embedded in body of simple Chocomint-style template
NAME_MINSHELL="minshell_chocomint"

cd ~/emsdk
# shellcheck disable=SC1091
source ./emsdk_env.sh
cd - >/dev/null

name_project=$(basename "$(realpath .)")
path_libraylib=~/raylib/wasm/libraylib.a
path_raylib_h=~/raylib/src
path_minshell="scripts/wasm/supplement/$NAME_MINSHELL.html"

mkdir -p build
for path_c in src/*.c; do
    stem="$(basename -s .c "$path_c")"
    path_o="build/$stem.o"
    emcc -Iinclude -I. -I"$path_raylib_h" -c "$path_c" -o "$path_o" \
        "$(pkg-config --cflags raylib 2>/dev/null || true)" -DPLATFORM_WEB
done

# Link object files into final HTML/WASM output
emcc build/*.o "$path_libraylib" -o "$name_project.html" -Os -Wall \
    -I. -I"$path_raylib_h" -L"$(dirname "$path_libraylib")" \
    "$(pkg-config --cflags --libs raylib 2>/dev/null || true)" \
    -s USE_GLFW=3 --shell-file "$path_minshell" -DPLATFORM_WEB \
    --preload-file assets -s TOTAL_MEMORY=67108864
