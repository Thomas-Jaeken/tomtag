#!/bin/bash
set -e -u -x

function repair_wheel {
    wheel="$1"
    if ! auditwheel show "$wheel"; then
        echo "Skipping non-platform wheel $wheel"
    else
        auditwheel repair "$wheel" --plat "$PLAT" -w dist
    fi
}

/opt/python/cp38*/bin/python -m build -s

# Compile wheels
for PYBIN in /opt/python/cp3[89]*/bin /opt/python/cp31*/bin; do
    "${PYBIN}/python" -m build -w
done

# # Bundle external shared libraries into the wheels
# for whl in dist/*.whl; do
#     repair_wheel "$whl"
# done
