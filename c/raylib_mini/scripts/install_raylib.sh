#!/bin/bash
set -euo pipefail

### Installs raylib system-wide (if needed)
### Last updated: 2026/08/03

sudo apt update
sudo apt install build-essential git clang pkg-config cmake -y
sudo apt install libasound2-dev libx11-dev libxrandr-dev \
    libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
    libxinerama-dev libwayland-dev libxkbcommon-dev -y

cd ~
if [[ -d raylib ]]; then
    echo "Raylib directory found, skipping cloning"
else
    git clone --depth=1 https://github.com/raysan5/raylib.git
fi

cd "raylib"
cmake -S . -B build -DRAYLIB_SHARE=OFF -DBUILD_EXAMPLES=OFF
sudo cmake --build build --target install
sudo ldconfig
