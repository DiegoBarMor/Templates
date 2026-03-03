import sys
import shutil
from pathlib import Path

# ------------------------------------------------------------------------------
def _replace_all(path: Path, old: str, new: str):
    if not path.exists():
        print(f"--- Skipping '{path}' (doesn't exist)")
        return

    path.write_text(
        path.read_text().replace(old, new)
    )
    print(f">>> Replaced '{old}' with '{new}' in '{path}'")


# ------------------------------------------------------------------------------
def template_c_raylib(variant: str = ""):
    path_template = ROOT / f"c/raylib_{variant}"
    shutil.copytree(path_template, PATH_NEW_PROJECT)
    _replace_all(PATH_NEW_PROJECT / ".gitignore",   "raylib_project", NAME_NEW_PROJECT)
    _replace_all(PATH_NEW_PROJECT / "README.md",    "Raylib Project", NAME_NEW_PROJECT)
    _replace_all(PATH_NEW_PROJECT / "src/params.c", "Raylib Project", NAME_NEW_PROJECT)


# ------------------------------------------------------------------------------
def template_py_pip():
    path_template = ROOT / "python/pip_project"
    shutil.copytree(path_template, PATH_NEW_PROJECT)
    shutil.move(PATH_NEW_PROJECT / "pip_project", PATH_NEW_PROJECT / NAME_NEW_PROJECT )
    for path_file in ["environment.yml", "install.sh", "README.md", "setup.py", "upload.sh"]:
        _replace_all(PATH_NEW_PROJECT / path_file, "pip_project", NAME_NEW_PROJECT)


# ------------------------------------------------------------------------------
def template_website():
    path_template = ROOT / "web/simple_website"
    shutil.copytree(path_template, PATH_NEW_PROJECT)


# ------------------------------------------------------------------------------
def main():
    templates = {
        "c_raylib_mini" : ( template_c_raylib, ("mini"   ,) ),
        "c_raylib_mod"  : ( template_c_raylib, ("modular",) ),
        "c_raylib_wasm" : ( template_c_raylib, ("wasm"   ,) ),
        "py_pip"        : ( template_py_pip  , ()           ),
        "website"       : ( template_website , ()           ),
    }
    str_available = f"Available templates: {' '.join(templates.keys())}"

    if not NAME_TEMPLATE:
        print(str_available)
        exit(-1)

    if NAME_TEMPLATE not in templates:
        raise ValueError(
            f"Template '{NAME_TEMPLATE}' is not available. " + str_available
        )

    func,args = templates[NAME_TEMPLATE]
    func(*args)


################################################################################
if __name__ == "__main__":
    PATH_NEW_PROJECT = Path(sys.argv[1])
    NAME_TEMPLATE = sys.argv[2]
    ROOT = Path(__file__).parent

    NAME_NEW_PROJECT = PATH_NEW_PROJECT.name.replace(' ', '_') # ensure there are no spaces in the name...
    PATH_NEW_PROJECT = PATH_NEW_PROJECT.parent / NAME_NEW_PROJECT

    if PATH_NEW_PROJECT.exists():
        print(f"XXX '{PATH_NEW_PROJECT}' already exists. Skipping.")
        exit(-1)

    main()


################################################################################
