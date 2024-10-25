#!/bin/bash

# Write a Program to find whether a given year is a leap year or not

echo -e -n "Enter year: "
  read year
 
if [ `expr $year % 4` -eq 0 -a `expr $year % 100` -ne 0 -o `expr $year % 400    ` ]
  then
     echo "leap"
else
     echo "not leap"
fi

