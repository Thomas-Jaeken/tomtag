# TomTag

This package holds several functions to process raw timetags that would be output by a tagger like e.g. a UQD Logic16.
Documentation:
https://tomtag.readthedocs.io/en/latest/index.html

Source code:
https://github.com/Thomas-Jaeken/tomtag

# Installation
```
pip install tomtag
```
This should build on all OS, but if for some reason you want to compile it yourself, clone this repo and execute: 
```
pip install .
```
This will compile the package from source and install it. To compile the package without installing, execute:
```
python3 -m build
```
This will produce a .whl file in the dist directory. This file can then be installed by executing
```
pip install dist/*.whl
```