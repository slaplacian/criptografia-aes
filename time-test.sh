#!/bin/bash

for i in {1..100}; do
    echo "Execution $i" >> times.txt
    ./aes $1 >> times.txt
    echo "" >> times.txt
done