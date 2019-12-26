#!/bin/bash

fileconf="/opt/nginx-1.13.9/conf/nginx.conf"

is_ms_enabled=$(cat $fileconf | grep 'modsecurity .*on' | wc -l)

if [ $is_ms_enabled -ge 1 ]
then
	sed -i "s/modsecurity on;/modsecurity off;/g" "$fileconf"
	echo "Modsecurity disabled"
else
	sed -i "s/modsecurity off;/modsecurity on;/g" "$fileconf"
	echo "Modsecurity enabled"
fi