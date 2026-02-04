from setuptools import setup, find_packages

setup(
    name="pip_project_nested",
    version="0.1.0",
    description="WIP_PLACEHHOLDER",
    keywords="",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author="DiegoBarMor",
    author_email="diegobarmor42@gmail.com",
    url="https://github.com/diegobarmor/pip_project_nested",
    license="MIT",
    package_dir={"": "src"},
    packages=find_packages(where="src"),
    package_data={ # optional
        "pip_project_nested": ["config.ini", "_data/*"],
    },
    install_requires=[],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.10",
)
