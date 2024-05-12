#!/bin/env bash

python3 -m venv .venv.wheel/
.venv.wheel/bin/python3 -m pip install cibuildwheel==2.18.0
.venv.wheel/bin/python3 -m cibuildwheel --output-dir wheelhouse