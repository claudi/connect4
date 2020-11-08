#!/bin/bash

population_size=$((${1}-1))

parallel --sshloginfile '..' --sshdelay 0.1 \
    --basefile play \
    --progress \
    --results output_{}.tsv \
    --cleanup \
    --joblog log \
    echo "{}"';' ::: `seq 0 ${population_size}` ::: `seq 0 ${population_size}`

return 0
