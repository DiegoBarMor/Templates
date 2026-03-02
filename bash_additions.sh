#!/bin/bash

boiler() { # FUNC: create a boilerplate file at the specified path, based on the file extension
    local path="${1}"
    if [ -z "$path" ]; then
        echo "Usage: boiler <file_path>"
        return 1
    fi

    python3 "$DIR_HSM/plugins/templates/apply_boilerplate.py" "$path"
}
