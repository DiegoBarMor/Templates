#!/bin/bash
set -euo pipefail

### Builds and runs the project.
### Last updated: 2026/08/03

if [ ! -f "main.cpp" ]; then
    echo "Error: script must be run in the project folder containing the 'main.cpp' file."
    exit 1
fi

bash scripts/build_project.sh

./build/main
