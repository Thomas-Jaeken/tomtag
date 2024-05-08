from setuptools import setup, Extension
import numpy as np


tomtag_module = Extension(
    "tomtag",
    sources=[
        'src/tomtag/correlation_module.c',
        'src/tomtag/correlation.c',
    ],
    include_dirs=[
        np.get_include(),
        'src/tomtag'
    ]
)


def main():
    setup(
        name='tomtag',
        version='0.11',
        description='time tag correlation library ',
        long_description='This package holds several functions to process raw timetags that would be output by a tagger like e.g. a UQD Logic16.',
        author='Thomas Jaeken',
        author_email='tj2022@hw.ac.uk',
        url='https://github.com/Thomas-Jaeken/tomtag',
        requires=['numpy'],
        ext_modules=[tomtag_module],
        classifiers=[
            'Programming Language :: Python :: 3',
            'License :: OSI Approved :: MIT License',
            'Operating System :: OS Independent',
        ],
    )

if __name__ == '__main__':
    main()