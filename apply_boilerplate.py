import sys
import shutil
from pathlib import Path

# ------------------------------------------------------------------------------
def module_c():
    name = PATH_NEW_FILE.stem
    parent_header = PATH_NEW_FILE.resolve().parent
    parent_source = Path(
        str(parent_header)[::-1].replace("include"[::-1], "src"[::-1], 1)[::-1]
    )
    parent_header.mkdir(parents = True, exist_ok = True)
    parent_source.mkdir(parents = True, exist_ok = True)

    shutil.copy(FOLDER_BOILERS / "module.c", parent_source / f"{name}.c")
    shutil.copy(FOLDER_BOILERS / "module.h", parent_header / f"{name}.h")


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

    shutil.copy(FOLDER_BOILERS / boilerplates[EXT], PATH_NEW_FILE)


################################################################################
if __name__ == "__main__":
    PATH_NEW_FILE = Path(sys.argv[1]) # [TODO] proper arg management
    IS_MODULE = (sys.argv[2].lower() != "") if len(sys.argv) > 2 else False
    # IS_MODULE = (sys.argv[2].lower() == "mod") if len(sys.argv) > 2 else False

    EXT = PATH_NEW_FILE.suffix
    FOLDER_BOILERS = Path(__file__).parent / "_boilerplate"
    main()


################################################################################
