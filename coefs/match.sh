#!/bin/bash

for coefsX in coefs/*.dat
do
    for coefsO in coefs/*.dat
    do
        ./play "4" "${coefsX}" "${coefsO}"
    done
done
