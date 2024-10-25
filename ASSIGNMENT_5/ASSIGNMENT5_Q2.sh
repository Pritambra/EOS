#!/bin/bash/


echo ""
echo "1. Date"
echo "2. Cal"
echo "3. Ls"
echo "4. Pwd"
echo "5. Exit"
echo -n "Enter your choice: "
read choice

case $choice in
1) date
;;
2) cal
;;
3) ls
;;
4) pwd
;;
5) exit
;;

esac
