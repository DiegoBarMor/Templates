import sys
import shutil
from pathlib import Path

# ------------------------------------------------------------------------------
def main():
    boilerplates = {
        ".html": "index.html",
        ".md" : "markdown.md",
        ".py" : "main.py",
        ".sh" : "script.sh",
    }
    if EXT not in boilerplates:
        raise ValueError(
            f"Boilerplate for extension '{EXT}' is not available. " +\
            f"Available extensions: {' '.join(boilerplates.keys())}"
        )
    shutil.copy(FOLDER_BOILERS / boilerplates[EXT], PATH_NEW_FILE)


################################################################################
if __name__ == "__main__":
    PATH_NEW_FILE = Path(sys.argv[1])
    EXT = PATH_NEW_FILE.suffix
    FOLDER_BOILERS = Path(__file__).parent / "_boilerplate"
    main()


################################################################################
