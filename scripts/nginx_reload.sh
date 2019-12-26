#!/bin/bash

entries_num=$(ps -aux | grep nginx | grep process | wc -l)

if [ $entries_num -ge 1 ]
then
	sudo /opt/nginx-1.13.9/sbin/nginx -s reload
	echo "Nginx reloaded"
else
	sudo /opt/nginx-1.13.9/sbin/nginx
	echo "Nginx started"
fi
