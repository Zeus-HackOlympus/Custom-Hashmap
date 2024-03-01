#!/bin/bash

for seed in $(seq 26 256); do
    for m in $(seq 0 256); do
        i=0
        sum=0
        for file in ./inputs/*; do
            echo -n "$file : "
            output=$(./encoder $seed $m <"$file" | tail -n 1)
            echo $output $seed $m
            sum=$(python3 -c "print($output + $sum)")
            i=$((i + 1))
        done

        echo "average std dev = $(python3 -c "print($sum / $i)") $seed $m"

        echo "============================================"

        i=0
        sum=0

        for file in ./inputs/*; do
            echo -n "$file : "
            output=$(./demo_encoder <"$file" | tail -n 1)
            echo $output
            sum=$(python3 -c "print($output + $sum)")
            i=$((i + 1))
        done

        echo "average std dev = $(python3 -c "print($sum / $i)")"
    done
done
