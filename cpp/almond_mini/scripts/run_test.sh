#!/bin/bash
set -euo pipefail

### Builds and runs the project, either with or without CMake
### Use the "-c" option to build with CMake, otherwise the project will be built without CMake.
### Last updated: 2026/08/06

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

use_cmake=false

while getopts "c" opt; do
    case $opt in
        c)
            use_cmake=true
            ;;
        *)
            echo "Usage: $0 [-c]"
            exit 1
            ;;
    esac
done

if [ "$use_cmake" = true ]; then
    bash scripts/cmake/build_project_cmake.sh
else
    bash scripts/build_project.sh
fi

./build/main
