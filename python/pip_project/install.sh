#!/bin/bash
set -eu

# Install the package locally

pip uninstall pip_project -y || true
pip install .
rm -rf build pip_project.egg-info
