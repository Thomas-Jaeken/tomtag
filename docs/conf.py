extensions = [
    'sphinx_c_autodoc',
    'sphinx.ext.autodoc',
    "sphinx.ext.autosummary",
    "breathe"
    # other extensions...
]

html_title = "Tomtag"


# Configuration options for sphinx_c_autodoc
sphinx_c_autodoc_config = {
    "c_source": ["."],
}

master_doc='index'

project = 'Tomtag'