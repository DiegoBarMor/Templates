#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

name_project=$(basename "$(realpath .)")

folder_out=$(realpath ~"/Desktop/gui_exec/$name_project")
mkdir -p "$folder_out" "assets"
rm   -rf "$folder_out/src" "$folder_out/include"

cp "compile_project_ubuntu.sh" "$folder_out/"
cp -r "assets"  "$folder_out/assets"
cp -r "include" "$folder_out/include"
cp -r "src"     "$folder_out/src"

cd "$folder_out"
./compile_project_ubuntu.sh
cd - >/dev/null

ts=$(date "+%Y%m%d_%H%M%S")
is_termux=$(echo "$PREFIX" | grep -o "com.termux")
if [ "$is_termux" ]; then
    echo "// $ts last compiled (termux)" >> "src/main.c"
else
    echo "// $ts last compiled (other)" >> "src/main.c"
    "$folder_out/$name_project" # run the executable
fi
