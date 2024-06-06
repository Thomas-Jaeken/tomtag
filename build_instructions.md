# instructions for build

first:
```python setup.py sdist bdist```
then:
```pip install dist/version```

# pypi upload
```twine upload dist/*```