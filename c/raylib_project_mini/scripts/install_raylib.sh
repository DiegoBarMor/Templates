#!/bin/bash
set -euo pipefail

sudo apt update
sudo apt install build-essential git clang pkg-config cmake -y
sudo apt install libasound2-dev libx11-dev libxrandr-dev \
    libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
    libxinerama-dev libwayland-dev libxkbcommon-dev -y

TMPDIR=$(mktemp -d /tmp/raylib-build-XXXX)
trap 'rm -rf "$TMPDIR"' EXIT

git clone https://github.com/raysan5/raylib.git "$TMPDIR"
cd "$TMPDIR"

cmake -S . -B build -DRAYLIB_SHARE=OFF -DBUILD_EXAMPLES=OFF
sudo cmake --build build --target install
sudo ldconfig
