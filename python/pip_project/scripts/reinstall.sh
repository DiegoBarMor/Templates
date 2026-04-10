#!/bin/bash
set -eu

### Re-install the package locally

pip uninstall pip_project -y || true
pip install .
rm -rf build pip_project.egg-info
