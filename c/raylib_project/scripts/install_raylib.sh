#!/bin/bash
set -euo pipefail

sudo apt update
sudo apt install build-essential clang pkg-config

TMPDIR=$(mktemp -d /tmp/raylib-build-XXXX)
trap 'rm -rf "$TMPDIR"' EXIT

git clone https://github.com/raysan5/raylib.git "$TMPDIR"
cd "$TMPDIR"

cmake -S . -B build -DRAYLIB_SHARE=OFF -DBUILD_EXAMPLES=OFF
sudo cmake --build build --target install
sudo ldconfig
