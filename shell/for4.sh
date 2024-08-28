#!/bin/bash

echo '==============$*==============='

for i in "$*"; do
  echo "ban zhang l $i";
done


echo '==============$@==============='

for j in "$@"; do
  echo "ban zhang l $j";
done