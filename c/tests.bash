#!/bin/bash
# Normalize the output 
input_file=$1
normalize(){
    echo "$1" | tr -s ' ' | sed 's/^ *//;s/ *$//'
}

n1=$(normalize "$(./ccwc "$input_file")" )
n2=$(normalize "$(wc "$input_file")")
n3=$(normalize "$(cat "$input_file"|./ccwc) $input_file")
 

# Compare the normalized sentences
if [ "$n1" = "$n2" ]; then
    echo "$input_file line reading : OK"
else
    echo "$input_file line reading : bad"
    diff "$n1" "$n2"
fi

if [ "$n2" = "$n3" ]; then
    echo "$input_file block reading : OK"
else
    echo "$input_file block reading : bad"
    diff "$n2" "$n3"
fi