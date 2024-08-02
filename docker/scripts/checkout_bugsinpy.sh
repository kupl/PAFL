#!/bin/bash
WORKSPACE=$(pwd)
export PATH=$PATH:"$WORKSPACE"/BugsInPy/framework/bin

# thefuck
for i in {1..32}; do
    if [ ! -d ./source/thefuck/thefuck-$i ]; then mkdir -p ./source/thefuck/thefuck-$i; fi
    bugsinpy-checkout -p thefuck -v 0 -i $i -w "$WORKSPACE/source/thefuck/thefuck-$i"
done

# fastapi
for i in {1..16}; do
    if [ ! -d ./source/fastapi/fastapi-$i ]; then mkdir -p ./source/fastapi/fastapi-$i; fi
    bugsinpy-checkout -p fastapi -v 0 -i $i -w "$WORKSPACE/source/fastapi/fastapi-$i"
done

# spacy
for i in {1..10}; do
    if [ ! -d ./source/spacy/spacy-$i ]; then mkdir -p ./source/spacy/spacy-$i; fi
    bugsinpy-checkout -p spacy -v 0 -i $i -w "$WORKSPACE/source/spacy/spacy-$i"
done

# youtube-dl
for i in {1..43}; do
    if [ ! -d ./source/youtube-dl/youtube-dl-$i ]; then mkdir -p ./source/youtube-dl/youtube-dl-$i; fi
    bugsinpy-checkout -p youtube-dl -v 0 -i $i -w "$WORKSPACE/source/youtube-dl/youtube-dl-$i"
done