#!/bin/bash
i=0
sum=0

for file in ./inputs/*; do
    echo -n "$file : "
    output=$(./encoder <"$file" | tail -n 1)
    echo $output
    sum=$(python3 -c "print($output + $sum)")
    i=$((i + 1))
done

echo "average std dev = $(python3 -c "print($sum / $i)")"
