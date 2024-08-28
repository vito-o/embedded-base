#!/bin/bash

function sum() 
{
  s=0
  for (( i = 0; i <= $1; i++)); do
    s=$[$s+$i]
  done

  echo "The sum is $s"
}

while [ 1 -eq 1 ]; do
  read -p "please input your num: " n
  sum $n
done