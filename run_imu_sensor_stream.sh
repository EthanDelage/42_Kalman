#!/bin/bash

N=$1
START_INDEX=$2
DURATION=$3
fail_count=0
fail_indices=()

for i in $(seq 1 $N); do
  INDEX=$((i + START_INDEX - 1))
  echo "Running imu-sensor instance $INDEX with duration $DURATION"

  ./imu-sensor-stream-macos -d $DURATION -s $INDEX
  status=$?
  
  if [ $status -ne 0 ]; then
    echo "Instance $INDEX returned non-zero ($status)"
    fail_count=$((fail_count + 1))
    fail_indices+=($INDEX)
  fi
done

echo "imu-sensor finished. Non-zero exit count: $fail_count"

if [ $fail_count -gt 0 ]; then
  echo "Failed instance indices: ${fail_indices[@]}"
fi
