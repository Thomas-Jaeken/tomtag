# TomTag

This package holds several functions to process raw timetags that would be output by a tagger like e.g. a UQD Logic16.
The assumption is that the data is stored as integer times the internal resolution of the machine.
The most powerful functions are ```histogram```which does what you expect, and ```sync```, which allows you to redefine the timetags based on a given signal that is trusted to be periodic (to a higher quality than the internal clock of the timetagger.)

A very simple use example is illustrated here:

https://github.com/Thomas-Jaeken/tomtag/blob/eadfe923e1eab1344aa1252ada93bb91cb31b046/example.py#L1-L10

# Installation
```
pip install tomtag
```
This should build on all OS, but if for some reason you want to compile it yourself, clone this repo and execute these: 
```
python setup.py sdist bdist_wheel
pip install dist/tomtag-0.6.tar.gz
```
