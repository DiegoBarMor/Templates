import sys
import shutil
from pathlib import Path

from copy_template import replace_all

# ------------------------------------------------------------------------------
def module_c():
    name = PATH_NEW_FILE.stem
    parent_header = PATH_NEW_FILE.resolve().parent
    str_parent_header = str(parent_header)
    parent_header.mkdir(parents = True, exist_ok = True)

    parent_source = Path(
        str_parent_header[::-1].replace("include"[::-1], "src"[::-1], 1)[::-1]
    )
    parent_source.mkdir(parents = True, exist_ok = True)

    path_c = parent_source / f"{name}.c"
    path_h = parent_header / f"{name}.h"

    shutil.copy(FOLDER_BOILERS / "module.c", path_c)
    shutil.copy(FOLDER_BOILERS / "module.h", path_h)

    name_pascal = ''.join(word.capitalize() for word in name.split('_'))
    replace_all(path_h, "OBJECT", name.upper())
    replace_all(path_h, "Object", name_pascal)
    replace_all(path_h, "object", name)

    idx = str_parent_header[::-1].find("include"[::-1])
    replace_all(path_c, "module.h",
        (f"{str_parent_header[-idx+1:]}/" if idx != -1 else "") + f"{name}.h"
    )
    replace_all(path_c, "Object", name_pascal)
    replace_all(path_c, "object", name)


# ------------------------------------------------------------------------------
def module_python():
    parent = PATH_NEW_FILE.parent
    path_init = parent / "__init__.py"
    parent.mkdir(parents = True, exist_ok = True)

    shutil.copy(FOLDER_BOILERS / "module.py", PATH_NEW_FILE)
    if not path_init.exists():
        shutil.copy(FOLDER_BOILERS / "__init__.py", parent / "__init__.py")


# ------------------------------------------------------------------------------
def main():
    boilerplates = {
        ".html": "index.html",
        ".md" : "markdown.md",
        ".py" : "main.py",
        ".sh" : "script.sh",
        ".c"  : "module.c",
        ".h"  : "module.h",
    }
    if EXT not in boilerplates:
        raise ValueError(
            f"Boilerplate for extension '{EXT}' is not available. " +\
            f"Available extensions: {' '.join(boilerplates.keys())}"
        )

    if EXT in (".c", ".h") and IS_MODULE:
        module_c()
        return

    if EXT == ".py" and IS_MODULE:
        module_python()
        return

    PATH_NEW_FILE.parent.mkdir(parents = True, exist_ok = True)
    shutil.copy(FOLDER_BOILERS / boilerplates[EXT], PATH_NEW_FILE)


################################################################################
if __name__ == "__main__":
    PATH_NEW_FILE = Path(sys.argv[1])
    IS_MODULE = (sys.argv[2].lower() != "") if len(sys.argv) > 2 else False # [TODO] proper arg management (i.e --mod/-m flag)

    if PATH_NEW_FILE.exists():
        proceed = input(f"File '{PATH_NEW_FILE}' already exists. Overwrite? (y/n) ")
        if proceed.lower() != "y":
            print("Aborting.")
            exit(-1)

    EXT = PATH_NEW_FILE.suffix
    FOLDER_BOILERS = Path(__file__).parent / "_boilerplate"
    main()


################################################################################
