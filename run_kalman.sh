#!/bin/bash

N=$1

for i in $(seq 1 $N); do
  sleep 1
  echo "Running kalman instance"
  .build/bin/kalman 
done
