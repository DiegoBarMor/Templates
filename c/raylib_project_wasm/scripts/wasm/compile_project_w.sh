#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

cd ~/emsdk
# shellcheck disable=SC1091
source ./emsdk_env.sh
cd - >/dev/null

name_project=$(basename "$(realpath .)")
path_libraylib=~/raylib/wasm/libraylib.a
path_minshell=~/raylib/src/minshell.html
path_raylib_h=~/raylib/src

emcc -o "$name_project.html" -Os -Wall src/main.c "$path_libraylib" \
    -I. -I"$path_raylib_h" -L"$(dirname "$path_libraylib")" \
    "$(pkg-config --cflags --libs raylib 2>/dev/null || true)" \
    -s USE_GLFW=3 --shell-file "$path_minshell" -DPLATFORM_WEB
