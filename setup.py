from distutils.core import setup, Extension
import numpy as np

def main():
    setup(
        name='tomtag',
        version='0.11',
        description='time tag correlation library ',
        long_description='This package holds several functions to process raw timetags that would be output by a tagger like e.g. a UQD Logic16.',
        author='Faris Redza',
        author_email='faris.redza1999@gmail.com',
        url='https://github.com/FarisRedza/tomtag',
        requires=['numpy'],
        ext_modules=[
            Extension(
                name='tomtag',
                sources=[
                    np.get_include(),
                    'src/tomtag/correlation_module.c',
                    'src/tomtag/correlation.c',
                    'src/tomtag/correlation.h',
                ],
            ),
        ],
        classifiers=[
            'Programming Language :: Python :: 3',
            'License :: OSI Approved :: MIT License',
            'Operating System :: OS Independent',
        ],
        include_dirs='src/tomtag'
    )

if __name__ == '__main__':
    main()