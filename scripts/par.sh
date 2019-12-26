#!/bin/bash


flag_new_par=1
new_par=""

filename=""


if [ $# -ge 1 ]
then
    for param in "$@"
    do
        case $param in
        "--paranoia")
            flag_new_par=0
            ;;

        *)
            if [ $flag_new_par -eq 0 ]
            then
                new_par="$param"
                flag_new_par=1
            else
                filename="$param"
            fi
            ;;
        esac
    done
fi


sed -i "s/setvar:tx\.paranoia_level=.*/setvar:tx\.paranoia_level=$new_par\"/g" "$filename"
echo "Paranoia level changed to $new_par"