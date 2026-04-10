from setuptools import setup, find_packages
from pathlib import Path

__version__: str
exec(Path("pip_project/_version.py").read_text())

setup(
    name="pip_project",
    version=__version__,
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
    install_requires=["numpy==2.3.4"],
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
