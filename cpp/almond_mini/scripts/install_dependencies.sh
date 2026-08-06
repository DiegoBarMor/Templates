#!/bin/bash
set -euo pipefail

### Installs dependencies for SFML system-wide
### Last updated: 2026/08/06

sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev \
    libharfbuzz-dev \
    libmbedtls-dev \
    libssh2-1-dev -y
