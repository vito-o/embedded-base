#!/bin/bash

case $1 in
  "1" | "3" )
  echo "c 1"
  ;;
  "2" | "4" )
  echo "c 2"
  ;;
  * )
  echo "c other"
  ;;
esac