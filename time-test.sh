#!/bin/bash

for test in $(ls test-cases | grep -v "teste.txt"); do
    TEST_NAME=$(echo $test | cut -d "." -f1)
    TEST_FILE=experiment-result/time/$TEST_NAME-times.txt
    rm -f $TEST_FILE
    for i in {1..100}; do
        echo "Execution $i" >> $TEST_FILE
        ./aes test-cases/$test >> $TEST_FILE
        echo "" >> $TEST_FILE
    done

    if [[ $1 == "times-only" ]]; then
        perl -0777 -i -pe "s/====    Plain.*?Plain Text ====//sg" $TEST_FILE > /dev/null
        perl -0777 -i -pe "s/===    Cipher.*?Cipher Text ===//sg" $TEST_FILE > /dev/null
    fi

done