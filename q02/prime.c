#!/bin/bash

echo "Enter the lower limit:"
read low
echo "Enter the upper limit:"
read high

echo "Prime numbers between $low and $high are:"

for (( num=low; num<=high; num++ ))
do
    if [ $num -lt 2 ]; then
        continue
    fi

    is_prime=1
    for (( i=2; i*i<=num; i++ ))
    do
        if [ $((num % i)) -eq 0 ]; then
            is_prime=0
            break
        fi
    done

    if [ $is_prime -eq 1 ]; then
        echo "$num"
    fi
done
