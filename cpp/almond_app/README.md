# App Template

## With global installation of SFML
1) Run `scripts/install_sfml.sh` to install SFML and its dependencies. This is a global installation and only needs to be done once for all SFML projects.
2) Use `scripts/run_test.sh` for building and testing the project.

## With local installation of SFML
1) Run `scripts/install_dependencies.sh` to install SFML dependencies.
2) Use `scripts/run_test.sh -c` for building and testing the project. The `-c` flag indicates that cmake is to be used for building SFML locally only for this project.
