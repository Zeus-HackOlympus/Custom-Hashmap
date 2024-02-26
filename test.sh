#!/bin/bash

for file in ./inputs/*; do
    echo -n "$file : "
    ./encoder <"$file" | tail -n 1
done
