#!/bin/bash

echo -n "Enter name of the file:"
read filename
if [ -e $filename ]
then
echo 'Last modification time is' `ls -l $filename | cut -d" " -f 6,7,8`
else
echo "file does not exist"
fi
