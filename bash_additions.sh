#!/bin/bash

boiler() { # FUNC: create a boilerplate file at the specified path, based on the file extension
    local path="${1}"
    local mod_flag="${2}"
    if [ -z "$path" ]; then
        echo "Usage: boiler <file_path> [\"mod\"]"
        return 1
    fi

    python3 "$DIR_HSM/plugins/templates/apply_boilerplate.py" "$path" "$mod_flag"
}

template() { # FUNC: create a template project at the specified path
    local path_new_project="${1}"
    local template_name="${2}"
    if [ -z "$path_new_project" ]; then
        echo "Usage: template <path_new_project> <template_name>"
        return 1
    fi

    python3 "$DIR_HSM/plugins/templates/copy_template.py" "$path_new_project" "$template_name"
}
