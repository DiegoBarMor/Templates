#!/bin/bash
set -euo pipefail

### Compile and link the project source files (using CMake)
### Must run "scripts/install_dependencies.sh" at some point first (once).
### Instead of relying in a global installation of SFML, this script will download and build SFML as a static library in the "build" folder.
### Last updated: 2026/08/09

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

cp scripts/cmake/CMakeLists.txt .

cmake -B build
cmake --build build

cp build/bin/app build/main
