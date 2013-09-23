#! /bin/bash

cat /dev/null > a_list.ckl
for((i=0; i<20000; i++)) {
    echo "C$(($RANDOM % 2))A Checklist Item $i" >> a_list.ckl
}
