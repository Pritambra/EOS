#!/bin/bash

#write a program to find the greatest of three numbers

echo "Enter num1: "
   read n1
 
echo "Enter num2: "
    read n2
 
echo "Enter num3: "
     read n3
 
if [ $n1 -gt $n2 ]
  then
      if [ $n1 -gt $n3 ]
        then
          echo "Num1 is greater: $n1"
      else
          echo "Num 3 is greater: $n3"
fi
else
   if [ $n2 -gt $n3 ]
      then
         echo "Num2 is greater: $n2"
    else
         echo "Num3 is greater: $n3" 
 fi
 fi

