#!/bin/bash

# write a program to find whether the number is positive or negative

echo "Enter the Number: "
read num

if [ $num -gt 0 ]
then 
echo "number is positive : $num"

elif [ $num -lt 0 ]
then
echo "number is negative : $num"

else
echo "number is zero : $num"

fi


