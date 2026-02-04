#!/bin/bash
set -eu

# Install the package locally

pip uninstall pip_project_nested -y || true
pip install .
rm -rf build pip_project_nested.egg-info
