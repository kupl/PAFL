#!/bin/bash

# cpp_peglib
for i in {1..10}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout cpp_peglib $i -b -t ./data/source
done

# cppcheck
for i in {1..30}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout cppcheck $i -b -t ./data/source
done

# exiv2
for i in {1..20}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout exiv2 $i -b -t ./data/source
done

# libchewing
for i in {1..8}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout libchewing $i -b -t ./data/source
done

# libxml2
for i in {1..7}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout libxml2 $i -b -t ./data/source
done

# proj
for i in {1..28}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout proj $i -b -t ./data/source
done

# openssl
for i in {1..28}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout openssl $i -b -t ./data/source
done

# yaml_cpp
for i in {1..10}; do
    python ./bugscpp/bugscpp/bugscpp.py checkout yaml_cpp $i -b -t ./data/source
done