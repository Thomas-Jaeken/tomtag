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
This should build on all OS, but if for some reason you want to compile it yourself, clone this repo and execute these: 
```
python setup.py sdist bdist_wheel
pip install dist/tomtag-0.6.tar.gz
```
NOTE: for python3.13 when compiling with gcc there is a warning upon compilation, but this can be circumvented by running:
```
CFLAGS="-Wno-error=incompatible-pointer-types" pip install tomtag
```
