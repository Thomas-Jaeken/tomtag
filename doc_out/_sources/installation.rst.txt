Installation Guide
================================

Tomtag can be installed on Windows, macOS, and Linux environments. The method is using pip, but you can also install Tomtag from source.

Prerequisites
-------------

Before installing tomtag, ensure you have Python 3.11 or newer installed on your system. You can verify your Python version by running:

.. code-block:: bash

   python3 --version

If you do not have Python installed, visit https://www.python.org/ for installation instructions.

Installing with pip
-------------------

The simplest way to install tomtag is using pip, Python's package installer. Run the following command in your terminal:

.. code-block:: bash

   pip install tomtag

This command will download and install Tomtag along with its required dependencies.

Installing from Source
----------------------

To install Tomtag from source, first, clone the repository from GitHub:

.. code-block:: bash

   git clone https://github.com/Thomas-Jaeken/tomtag.git
   cd tomtag

Then, install the project using:

.. code-block:: bash

   pip install .

This will install Tomtag directly from the source code.

Post-Installation
-----------------

After installing Tomtag, you can verify the installation by running:

.. code-block:: bash

   python -c "import tomtag; print(tomtag.__version__)"

You should see the version number of tomtag printed to the console.

Troubleshooting
---------------

If you encounter any issues during the installation process, please file an issue on the GitHub repository.

