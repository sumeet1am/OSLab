#!/bin/bash
echo "Enter the string to be checked"
read str
length=${#str}
reverse=""

for (( i=length-1; i>=0; i-- ))
do
    reverse=$reverse${str:$i:1}
done

if [[ $reverse == "$str" ]]
then
    echo "The string $str is a palindrome"
else
    echo "The string $str is not a palindrome"
fi
