#!/bin/bash

factorial() {
    local num=$1
    local result=1

    for (( i=1; i<=num; i++ ))
    do
        result=$((result * i))
    done

    echo $result
}


if [ $# -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi


number=$1


if ! [[ $number =~ ^[0-9]+$ ]]; then
    echo "Please enter a non-negative integer."
    exit 1
fi


fact=$(factorial $number)
echo "Factorial of $number is: $fact"

