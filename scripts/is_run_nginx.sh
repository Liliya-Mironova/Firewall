#!/bin/bash

entries_num=$(ps -aux | grep nginx | grep process | wc -l)

if [ $entries_num -eq 0 ]
then
	echo "Nginx is OFF"
else
	echo "Nginx is ON"
fi