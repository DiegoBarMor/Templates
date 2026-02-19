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
    _replace_all(PATH_NEW_PROJECT / ".gitignore",   "raylib_project", PATH_NEW_PROJECT.name.replace(" ", "\\ "))
    _replace_all(PATH_NEW_PROJECT / "README.md",    "Raylib Project", PATH_NEW_PROJECT.name)
    _replace_all(PATH_NEW_PROJECT / "src/params.c", "Raylib Project", PATH_NEW_PROJECT.name)


# ------------------------------------------------------------------------------
def main():
    available_templates = ("c_raylib", "c_raylib_mod", "c_raylib_wasm")
    match NAME_TEMPLATE:
        case "c_raylib":      template_c_raylib()
        case "c_raylib_mod":  template_c_raylib("_modular")
        case _: raise ValueError(f"Template '{NAME_TEMPLATE}' is not available. Available templates: {available_templates}")


################################################################################
if __name__ == "__main__":
    NAME_TEMPLATE = sys.argv[1]
    PATH_NEW_PROJECT = Path(sys.argv[2])
    ROOT = Path(__file__).parent
    main()


################################################################################
