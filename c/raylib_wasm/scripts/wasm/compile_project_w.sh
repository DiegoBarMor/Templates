#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

safe_copy_files() {
    ext=$1
    shopt -s nullglob
    files=(website/*."$ext")
    if [ ${#files[@]} -gt 0 ]; then
        cp "${files[@]}" ./
    fi
    shopt -u nullglob
}

###### options for NAME_SHELL
### minimal      -> plain canvas
### chocomint    -> canvas embedded in body of simple Chocomint-style template
### chocomint_io -> canvas embedded in body of simple Chocomint-style template; it has i/o capabilities with the WASM
NAME_SHELL="chocomint_io"

cd ~/emsdk
# shellcheck disable=SC1091
source ./emsdk_env.sh
cd - >/dev/null

path_libraylib=~/raylib/wasm/libraylib.a
path_raylib_h=~/raylib/src
path_shell="website/shell/$NAME_SHELL.html"

# rm -f ./*.html ./*.css ./*.js
safe_copy_files html
safe_copy_files css
safe_copy_files js

mkdir -p build
while IFS= read -r -d '' path_c; do
    stem="$(basename -s .c "$path_c")"
    path_o="build/$stem.o"
    emcc -Iinclude -I. -I"$path_raylib_h" -c "$path_c" -o "$path_o" \
        "$(pkg-config --cflags raylib 2>/dev/null || true)" -DPLATFORM_WEB
done <   <(find src -name '*.c' -print0)

### Link object files into final HTML/WASM output
emcc build/*.o "$path_libraylib" -o "app.html" -Os -Wall \
    -I. -I"$path_raylib_h" -L"$(dirname "$path_libraylib")" \
    "$(pkg-config --cflags --libs raylib 2>/dev/null || true)" \
    -s USE_GLFW=3 --shell-file "$path_shell" -DPLATFORM_WEB \
    --preload-file assets -s TOTAL_MEMORY=67108864 \
    -s EXPORTED_RUNTIME_METHODS=ccall
