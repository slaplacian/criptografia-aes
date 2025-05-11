# AES

## Como compilar:

    g++ -o aes main.cpp source/classes/* source/utils.cpp

## Como executar:

    ./aes arq.txt

A saída será algo como:
    
    ***Time to Key Expand: 5 ms
    ====    Plain Text     ====
    Ola mundo
    somos do IME
    ==== End of Plain Text ====
    ***Time to Encrypt: 97 ms
    ===    Cipher Text     ===
    �ep     �X����1Z�{���c�5���s�|6
    === End of Cipher Text ===
    ***Time to Decrypt: 174 ms
    ====    Plain Text     ====
    Ola mundo
    somos do IME
    ==== End of Plain Text ====

## Como foi implementado?

foi implementado usando a [FIPS](fips-aes.pdf).

## Teste de Memória

Foi feito utilizando valgrind, basta rodar memory-test.sh

    ./memory-test.sh

o resultado está em [memory](experiment-result/memory)

## Teste de tempo

basta rodar o time-test.sh

    ./time-test.sh

o resultado está em [test](experiment-result/test)
