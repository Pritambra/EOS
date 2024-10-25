#!/bin/bash

echo "Enter file name : "
read path

if [ -e $path ]
then 
   if [ -d $path ]
   then 
       echo "File is directory"

	   elif [ -f $path ]
	   then 
	       echo "Regular file"
		   if [ -x $path ]
		   then 
		      echo "File has executable permission"

	        fi
    fi
else
    echo "File does not exist"

fi

