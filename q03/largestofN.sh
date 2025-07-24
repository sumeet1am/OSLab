#!/bin/bash

echo "Enter the number of elements:"
read n

echo "Enter $n numbers:"
for (( i=0; i<n; i++ ))
do
    read arr[i]
done

largest=${arr[0]}

for (( i=1; i<n; i++ ))
do
    if [ ${arr[i]} -gt $largest ]; then
        largest=${arr[i]}
    fi
done

echo "The largest number is: $largest"
