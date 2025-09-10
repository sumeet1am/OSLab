#!/bin/bash

# Read dimensions
echo -n "Enter number of rows: "
read rows
echo -n "Enter number of columns: "
read cols

# Read first matrix
echo "Enter elements of first matrix ($rows x $cols):"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        read a[$((i*cols + j))]
    done
done

# Read second matrix
echo "Enter elements of second matrix ($rows x $cols):"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        read b[$((i*cols + j))]
    done
done

# Display first matrix
echo "First Matrix:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        echo -n "${a[$((i*cols + j))]} "
    done
    echo
done

# Display second matrix
echo "Second Matrix:"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        echo -n "${b[$((i*cols + j))]} "
    done
    echo
done

# Compute and display sum
echo "Resultant Matrix (Sum):"
for ((i=0; i<rows; i++))
do
    for ((j=0; j<cols; j++))
    do
        idx=$((i*cols + j))
        sum=$(( a[idx] + b[idx] ))
        echo -n "$sum "
    done
    echo
done
