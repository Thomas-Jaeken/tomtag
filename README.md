# TomTag

This package holds 2 functions at the moment, ```count()``` and ```get_cc()```.
Both take as input a numpy array of integers and a coincidence window (also integer) and finds the entries that are less than the coincidence window apart.
```count()``` only counts these entries, but ```get_cc()``` also returns the indices of both arrays.

The integers are in the internal units of the timetagger so the user would need to know this to convert.

The use of the functions is verry simple and illustrated here:

https://github.com/Thomas-Jaeken/tomtag/blob/eadfe923e1eab1344aa1252ada93bb91cb31b046/example.py#L1-L10

# Installation
The project is not yet listed on pipy
To install the module to your computer, download the .tar.gz file from the ```dist``` folder and execute
```
pip install $PATH/tomtag-0.2.tar.gz
```
