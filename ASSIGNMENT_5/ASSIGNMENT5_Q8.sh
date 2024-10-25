#!/bin/bash

#!/bin/bash

# print table of given number.



echo "Enter Num : "
read n1
i=1
while [ $i -le 10 ]
do
	res=`expr $i \* $n1`
	echo "$res"
	i=`expr $i + 1`
done


i=1

until [ $i -gt 10 ]
do
	res=`expr $i \* $n1`
	echo -n -e "$res "
	i=`expr $i + 1`
done







