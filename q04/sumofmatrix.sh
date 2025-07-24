#!/bin/bash

echo "Enter number of rows:"
read rows
echo "Enter number of columns:"
read cols

echo "Enter elements of Matrix A:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        read a[$i,$j]
    done
done

echo "Enter elements of Matrix B:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        read b[$i,$j]
    done
done

# Display Matrix A
echo "Matrix A:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        echo -n "${a[$i,$j]} "
    done
    echo
done

# Display Matrix B
echo "Matrix B:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        echo -n "${b[$i,$j]} "
    done
    echo
done

# Matrix Addition and Display
echo "Resultant Matrix After Addition:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        sum=$(( ${a[$i,$j]} + ${b[$i,$j]} ))
        echo -n "$sum "
    done
    echo
done
