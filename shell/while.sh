#!/bin/bash
s=0
i=1
while [ $i -le 100 ]; do
  s=$[$s+$i]
  i=$[$i+1]
done

echo "the number of s is ${s}"
echo "the number of i is ${i}"