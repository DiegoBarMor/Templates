import sys
import shutil
from pathlib import Path

# ------------------------------------------------------------------------------
def _replace_all(path: Path, old: str, new: str):
    path.write_text(
        path.read_text().replace(old, new)
    )
    print(f">>> Replaced '{old}' with '{new}' in '{path}'")


# ------------------------------------------------------------------------------
def template_c_raylib(variant: str = ""):
    path_template = ROOT / f"c/raylib_project{variant}"
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
def main():
    available_templates = ("c_raylib", "c_raylib_mod", "c_raylib_wasm")
    match NAME_TEMPLATE:
        case "c_raylib":      template_c_raylib()
        case "c_raylib_mod":  template_c_raylib("_modular")
        case "c_raylib_wasm": template_c_raylib("_wasm")
        case "py_pip":        template_py_pip()
        case _: raise ValueError(f"Template '{NAME_TEMPLATE}' is not available. Available templates: {available_templates}")


################################################################################
if __name__ == "__main__":
    NAME_TEMPLATE = sys.argv[1]
    PATH_NEW_PROJECT = Path(sys.argv[2])
    ROOT = Path(__file__).parent

    NAME_NEW_PROJECT = PATH_NEW_PROJECT.name.replace(' ', '_') # ensure there are no spaces in the name...
    PATH_NEW_PROJECT = PATH_NEW_PROJECT.parent / NAME_NEW_PROJECT
    main()


################################################################################
