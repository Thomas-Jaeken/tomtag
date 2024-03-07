# setup.py

from setuptools import setup, Extension
import numpy as np

setup(
    name='tomtag',
    version='0.10',
    ext_modules=[
        Extension(
            name="tomtag",  # as it would be imported
            # may include packages/namespaces separated by `.`

            # all sources are compiled into a single binary file
            sources=["correlation_module.c", "correlation.c"],
            include_dirs=[np.get_include(),
                "/Users/thomasjaeken/Desktop/school/PhD/timetagging/tomtag/"
                ]
        ),
    ]
)
