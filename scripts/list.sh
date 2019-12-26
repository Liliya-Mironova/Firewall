#!/bin/bash

ip=""

filename=""


function AddWhiteList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, allow" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        str_prev=`grep "log, [allow|deny]" "$filename" | tail -n1`
        #echo "str_prev = $str_prev"

        str_prev_beg="${str_prev%, phase*}"
        #echo "str_prev_beg = $str_prev_beg"

        id_prev="${str_prev_beg##*id:}"
        #echo "id_prev = $id_prev"

        let "id = id_prev + 1"
        #echo "id = $id"

        echo "" >> "$filename"
        echo "SecRule REMOTE_ADDR \"@ipMatch $ip\" \"id:$id, phase:1, log, allow, t:none, ctl:ruleEngine=On, setvar:tx.crs_debug_mode=0\"" >> "$filename"
    fi
}

function RmWhiteList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, allow" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        echo "Can't delete $ip: it is not in whitelist"
    else
        sed -i "/$ip.*log, allow/d" "$filename"
        echo "$ip removed from the whitelist"
    fi
}

function GetWhiteList ()
{
    sz=`grep -E "[^0-9]* [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+.*log, allow" "$filename" | grep -o -E "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" | wc -l`

    list=`grep -E "[^0-9]* [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+.*log, allow" "$filename" | grep -o -E "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+"`

    if [ $sz -eq 0 ]
    then
        echo "Whitelist is empty"
    else
        echo "Whitelist:"
        echo "$list"
    fi
}

function FindWhiteList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, allow" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        echo "IP $ip is NOT in whitelist"
    else
        echo "IP $ip is in whitelist"
    fi
}

function AddBlackList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, deny" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        str_prev=`grep "log, [allow|deny]" "$filename" | tail -n1`
        #echo "str_prev = $str_prev"

        str_prev_beg="${str_prev%, phase*}"
        #echo "str_prev_beg = $str_prev_beg"

        id_prev="${str_prev_beg##*id:}"
        #echo "id_prev = $id_prev"

        let "id = id_prev + 1"
        #echo "id = $id"

        echo "" >> "$filename"
        echo "SecRule REMOTE_ADDR \"@ipMatch $ip\" \"id:$id, phase:1, log, deny, t:none, ctl:ruleEngine=On, setvar:tx.crs_debug_mode=0\"" >> "$filename"
    fi
}

function RmBlackList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, deny" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        echo "Can't delete $ip: it is not in blacklist"
    else
        sed -i "/$ip.*log, deny/d" "$filename"
        echo "$ip removed from the blacklist"
    fi
}

function GetBlackList ()
{
    sz=`grep -E "[^0-9]* [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+.*log, deny" "$filename" | grep -o -E "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+" | wc -l`

    list=`grep -E "[^0-9]* [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+.*log, deny" "$filename" | grep -o -E "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+"`

    if [ $sz -eq 0 ]
    then
        echo "Blacklist is empty"
    else
        echo "Blacklist:"
        echo "$list"
    fi
}

function FindBlackList ()
{
    sz=`grep -E "[^0-9]* $ip.*log, deny" "$filename" | wc -l`

    if [ $sz -eq 0 ]
    then
        echo "IP $ip is NOT in blacklist"
    else
        echo "IP $ip is in blacklist"
    fi
}

add_white=1
add_black=1

rm_white=1
rm_black=1

find_white=1
find_black=1

ip_addition_flag=1

if [ $# -ge 1 ]
then
    for param in "$@"
    do
        case $param in
        "--get-white")
            GetWhiteList
            ;;

        "--get-black")
            GetBlackList
            ;;

        "--get-all")
            echo "Whitelist:"
            GetWhiteList
            echo "Blacklist:"
            GetBlackList
            ;;

        "--add-white")
            add_white=0
            ip_addition_flag=0
            ;;

        "--add-black")
            add_black=0
            ip_addition_flag=0
            ;;

        "--rm-white")
            rm_white=0
            ip_addition_flag=0
            ;;

        "--rm-black")
            rm_black=0
            ip_addition_flag=0
            ;;

        "--find-white")
            find_white=0
            ip_addition_flag=0
            ;;

        "--find-black")
            find_black=0
            ip_addition_flag=0
            ;;

        *)
            if [ $ip_addition_flag -eq 0 ]
            then
                ip="$param"
                ip_addition_flag=1
            else
                filename="$param"
            fi
            ;;
        esac
    done
fi

if [ $add_white -eq 0 ]
then
    AddWhiteList
fi

if [ $add_black -eq 0 ]
then
    AddBlackList
fi

if [ $rm_white -eq 0 ]
then
    RmWhiteList
fi

if [ $rm_black -eq 0 ]
then
    RmBlackList
fi

if [ $find_white -eq 0 ]
then
    FindWhiteList
fi

if [ $find_black -eq 0 ]
then
    FindBlackList
fi
