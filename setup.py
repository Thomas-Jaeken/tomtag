import setuptools
import numpy as np


def get_version():
    with open('pyproject.toml') as f:
        pass


tomtag_module = setuptools.Extension(
    name="tomtag",
    sources=[
        'src/tomtag/correlation_module.c',
        'src/tomtag/correlation.c',
    ],
    include_dirs=[
        np.get_include(),
        'src/tomtag'
    ],
    language='c'
)

if __name__ == '__main__':
    setuptools.setup(
        name='tomtag',
        version='0.11',
        description='time tag correlation library ',
        long_description=open("README.md").read(),
        long_description_content_type='text/markdown',
        author='Thomas Jaeken',
        author_email='tj2022@hw.ac.uk',
        url='https://github.com/Thomas-Jaeken/tomtag',
        requires=['numpy'],
        packages=setuptools.find_packages('src'),
        package_dir={'': 'src'},
        ext_modules=[tomtag_module],
        classifiers=[
            'Programming Language :: Python :: 3',
            'License :: OSI Approved :: MIT License',
            'Operating System :: OS Independent',
        ],
        python_requires='>=3.8'
    )