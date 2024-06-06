from setuptools import setup, Extension
import numpy as np

setup_args = dict(
    ext_modules = [
        Extension(
            name='tomtag',
            sources=[
                'src/tomtag/correlation.c',
                'src/tomtag/correlation_module.c',
            ],
            include_dirs=[
                np.get_include(),
                'src/tomtag'
            ],
        )
    ],
    package_data={"": ["*.h"]}
)
setup(**setup_args)