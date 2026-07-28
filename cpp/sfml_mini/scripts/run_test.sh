#!/bin/bash
set -euo pipefail

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

bash scripts/compile_project.sh

./build/main
