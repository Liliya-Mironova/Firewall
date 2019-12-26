#!/bin/bash

ip=""

fileserv="/opt/nginx-1.13.9/conf/nginx-serv.conf"
fileprox="/opt/nginx-1.13.9/conf/nginx-proxy.conf"

fileconf="/opt/nginx-1.13.9/conf/nginx.conf"

ip_addition_flag=1

addserv=1
addprox=1

if [ $# -ge 1 ]
then
    for param in "$@"
    do
        case $param in
        "--ip")
            ip_addition_flag=0
            ;;

        "--add-serv")
            addserv=0
            addprox=1
            ;;

        "--add-prox")
            addprox=0
            addserv=1
            ;;

        *)
            if [ $ip_addition_flag -eq 0 ]
            then
                ip="$param"
                ip_addition_flag=1
            fi
            ;;
        esac
    done
fi

if [ $addprox -eq 0 ]
then
    cp $fileprox $fileconf
    sed -i "s/proxy_pass http:\/\/0\.0\.0\.0/proxy_pass http:\/\/$ip/g" $fileconf
    echo "Mode: reverse proxy"
fi

if [ $addserv -eq 0 ]
then
    cp $fileserv $fileconf
    echo "Mode: server"
fi