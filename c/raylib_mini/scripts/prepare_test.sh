#!/bin/bash
set -euo pipefail

### Creates a folder on a second location and copies scripts and assets to it.
### Last updated: 2026/08/03

if [ ! -f "main.c" ]; then
    echo "Error: script must be run in the project folder containing the 'main.c' file."
    exit 1
fi

name_project=$(basename "$(realpath .)")
folder_out=~/Desktop/gui_exec/$name_project

rm   -rf "$folder_out"
mkdir -p "$folder_out"

cp -r "scripts" "$folder_out/scripts"
if [ -d "assets" ]; then
    cp -r "assets"  "$folder_out/assets"
fi
