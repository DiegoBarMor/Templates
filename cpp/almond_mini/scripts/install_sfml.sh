#!/bin/bash
set -euo pipefail

### Installs SFML system-wide (if needed)
### Last updated: 2026/08/06

if [ ! -d "scripts" ]; then
    echo "Error: script must be run in the project folder containing the 'scripts' directory."
    exit 1
fi

bash scripts/install_dependencies.sh

cd ~
if [[ -d sfml ]]; then
    echo "SFML directory found, skipping cloning"
else
    git clone --depth 1 --branch 3.1.0 https://github.com/sfml/sfml.git
fi

cd "sfml"
cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DSFML_BUILD_EXAMPLES=OFF \
    -DSFML_BUILD_TEST_SUITE=OFF \
    -DSFML_BUILD_DOC=OFF \
    -DSFML_BUILD_AUDIO=ON \
    -DSFML_BUILD_GRAPHICS=ON \
    -DSFML_BUILD_WINDOW=ON \
    -DSFML_BUILD_NETWORK=ON \
    -DSFML_USE_SYSTEM_DEPS=ON \
    -DSFML_INSTALL_PKGCONFIG_FILES=ON
sudo cmake --build build --target install
sudo ldconfig

### Available options (https://www.sfml-dev.org/tutorials/3.1/getting-started/build-from-source/#configuring-your-sfml-build):
### -DCMAKE_BUILD_TYPE
### -DCMAKE_INSTALL_PREFIX
### -DBUILD_SHARED_LIBS  # defaults to OFF (static libraries)
### -DSFML_BUILD_EXAMPLES
### -DSFML_BUILD_TEST_SUITE
### -DSFML_BUILD_DOC
### -DSFML_BUILD_AUDIO
### -DSFML_BUILD_GRAPHICS
### -DSFML_BUILD_WINDOW
### -DSFML_BUILD_NETWORK
### -DSFML_USE_SYSTEM_DEPS
### -DSFML_INSTALL_PKGCONFIG_FILES
