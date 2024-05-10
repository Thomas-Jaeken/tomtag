prefix = $(HOME)/test

all: src/

build: src/
	python3 -m build

install: build

.PHONY: all build install