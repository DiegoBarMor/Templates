#!/bin/bash

boiler() { # FUNC: create a boilerplate file at the specified path, based on the file extension
    local path="${1}"
    if [ -z "$path" ]; then
        echo "Usage: boiler <file_path>"
        return 1
    fi

    python3 "$DIR_HSM/plugins/templates/apply_boilerplate.py" "$path"
}

template() { # FUNC: create a template project at the specified path
    local template_name="${1}"
    local path_new_project="${2}"
    if [ -z "$template_name" ]; then
        echo "Usage: template <template_name> <path_new_project>"
        return 1
    fi

    python3 "$DIR_HSM/plugins/templates/copy_template.py" "$template_name" "$path_new_project"
}
