#!/bin/bash
set -euo pipefail

if [ ! -d "src" ] || [ ! -d "include" ]; then
    echo "Error: script must be run in the project folder containing 'src' and 'include' directories."
    exit 1
fi

append_timestamp=false

name_project=$(basename "$(realpath .)")
folder_out=~/Desktop/gui_exec/$name_project

if [ ! -d "$folder_out" ]; then
    scripts/prepare_test.sh
fi

rm -rf "$folder_out/src" "$folder_out/include"

cp -r "include" "$folder_out/include"
cp -r "src"     "$folder_out/src"

cd "$folder_out"
bash scripts/compile_project.sh
cd - >/dev/null

if [ -z "${PREFIX+x}" ]; then # safe test for PREFIX even with "set -u"
    is_termux=""
else
    is_termux=$(printf '%s' "$PREFIX" | grep -o "com.termux" || true)
fi

ts=$(date "+%Y%m%d_%H%M%S")
if [ ! "$is_termux" ]; then
    if [ $append_timestamp == "true" ]; then
        echo "// $ts last compiled (other)" >> "src/main.c"
    fi

    ### run the executable
    "$folder_out/$name_project"

elif [ $append_timestamp == "true" ]; then
    echo "// $ts last compiled (termux)" >> "src/main.c"
fi
