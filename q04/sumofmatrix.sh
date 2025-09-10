#!/bin/bash

# Read size
echo "Enter rows:"
read r
echo "Enter cols:"
read c

# Read first matrix
echo "Enter first matrix:"
for ((i=0;i<r*c;i++))
do
  read a[$i]
done

# Read second matrix
echo "Enter second matrix:"
for ((i=0;i<r*c;i++))
do
  read b[$i]
done

# Print first matrix
echo "First matrix:"
k=0
for ((i=0;i<r;i++))
do
  for ((j=0;j<c;j++))
  do
    echo -n "${a[$k]} "
    ((k++))
  done
  echo
done

# Print second matrix
echo "Second matrix:"
k=0
for ((i=0;i<r;i++))
do
  for ((j=0;j<c;j++))
  do
    echo -n "${b[$k]} "
    ((k++))
  done
  echo
done

# Print sum matrix
echo "Sum matrix:"
k=0
for ((i=0;i<r;i++))
do
  for ((j=0;j<c;j++))
  do
    echo -n "$(( ${a[$k]} + ${b[$k]} )) "
    ((k++))
  done
  echo
done
