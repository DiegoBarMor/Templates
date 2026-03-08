# Raylib Project
1) Run `scripts/install_raylib_emcc.sh` to install raylib and its dependencies. For this template, emcc is also installed for dealing with WASM.
2) Run `scripts/prepare_test.sh` to set up an external directory (`~/Desktop/gui_exec/Raylib Project`) for building and testing the project. This will re-create the directory, copy the `scripts/` directory and copy the `assets/` directory (if present).
3) This step depends on the target testing:
    - **For non-web**: Use `scripts/run_test.sh` for building and testing the project. This will updated the external directory with any changes in source/header files.
    - **For web**: Use `scripts/wasm/run_test_w.sh` instead. This will start hosting a local server and open a firefox tab for testing the WASM. The server will be terminated either by closing the firefox tab or by pressing `q` in the terminal.
