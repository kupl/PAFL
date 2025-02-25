#!/bin/bash

docker build --tag pafl $(pwd)
docker run --rm -it -v $(pwd):/workspace pafl
