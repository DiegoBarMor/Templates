#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

name_project=$(basename "$(realpath .)")
folder_out=$(realpath ~"/Desktop/gui_exec/$name_project")

rm   -rf "$folder_out"
mkdir -p "$folder_out"

cp "compile_project_ubuntu.sh" "$folder_out/"
if [ -d "assets" ]; then
    cp -r "assets"  "$folder_out/assets"
fi
