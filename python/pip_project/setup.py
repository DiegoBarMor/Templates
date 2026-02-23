from setuptools import setup, find_packages
from pathlib import Path

def read_requirements(path = "requirements.txt"):
    p = Path(path)
    if not p.exists(): return []
    stripped_lines = (ln.strip() for ln in p.read_text().strip().splitlines())
    return [ln for ln in stripped_lines if ln and not ln.startswith("#")]

setup(
    name="pip_project",
    version="0.1.0",
    description="Package description",
    keywords="",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author="DiegoBarMor",
    author_email="diegobarmor42@gmail.com",
    url="https://github.com/diegobarmor/pip_project",
    license="MIT",
    packages=find_packages(),
    package_data={ # optional
        "pip_project": ["config.ini", "_data/*"],
    },
    install_requires=read_requirements(), # replace with install_requires=[] if there are no requirements
    entry_points={ # comment out if package is intended to be used only via imports
        "console_scripts": [
            "pip_project=pip_project.__main__:main",
        ],
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.10",
)
