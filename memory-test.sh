#!/bin/bash

for test in $(ls test-cases | grep -v "teste.txt"); do
    TEST_NAME=$(echo $test | cut -d "." -f1)
    TEST_FILE=experiment-result/memory/$TEST_NAME-memory.out
    rm -f $TEST_FILE
    valgrind --tool=massif --massif-out-file=$TEST_FILE --time-unit=ms --detailed-freq=1 --stacks=yes ./aes test-cases/$test > /dev/null
done