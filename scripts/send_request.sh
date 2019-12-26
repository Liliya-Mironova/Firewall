#!/bin/bash

flag_new_req=1
new_req=""

if [ $# -ge 1 ]
then
    for param in "$@"
    do
        case $param in
        "--request")
            flag_new_req=0
            ;;

        *)
            if [ $flag_new_req -eq 0 ]
            then
                new_req="$param"
                flag_new_req=1
            fi
            ;;
        esac
    done
fi

curl $new_req || echo "Invalid request"