#!/bin/bash

num_see=0
see_flag=1

filename=""


if [ $# -ge 1 ]
then
    for param in "$@"
    do
        case $param in
        "-n")
            see_flag=0
            ;;

        *)
            if [ $see_flag -eq 0 ]
            then
                num_see="$param"
                see_flag=1
            else
                filename="$param"
            fi
            ;;
        esac
    done
fi

if [ $num_see -ne 0 ]
then
    #out=`grep -o "^.*\[error\].*ModSecurity:.*\[msg \"[^\"]*\"\]" $filename | tail --lines=$num_see`
    out=`grep -r "ModSecurity" $filename | tail --lines=$num_see`

    sz=`grep -r "ModSecurity" $filename | tail --lines=$num_see | wc -l`
    #echo "$out"
    #echo "$sz"

    if [ $sz -eq 0 ]
    then
        echo "No messages from ModSecurity in log file"
    else
        echo "$out" | while read line
        do
            echo "------------------------------------------------------------------------------------------------------------"

            #time=${line% \[error\]*}
            tm=${line%\ [info*}
            tm=${tm%\ [warn*}
            time=${tm#*\ }
            echo "time      = $time"

            msg_with_end=${line##*\[msg \"}
            #msg=${msg_with_end%\"\]}
            msg=${msg_with_end%\"] [data*}
            echo "msg      = $msg"

            rq=${line##*request:\ \"}
            request=${rq%\",*}
            echo "request = $request"

            #client_begin=${line%\] ModSecurity*}
            cl=${line##*client:\ }
            client=${cl%, server*}
            echo "client = $client"
        done
    fi
fi
