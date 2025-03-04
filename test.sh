#!/bin/bash
CHECKER="./bin/checker"
TEST_DIR="./test/"
CUDA="./bin/cuda"

for TEST_FILE in "${TEST_DIR}"*; do
    if [[ -f "$TEST_FILE" ]]; then
        echo "Testing: $TEST_FILE"
        $CHECKER < "$TEST_FILE"
    fi
done

echo "--- Now testing bitonic sort on CUDA ---"
for TEST_FILE in "${TEST_DIR}"*; do
    if [[ -f "$TEST_FILE" ]]; then
        echo "Testing: $TEST_FILE"
        $CUDA < "$TEST_FILE" 
    fi
done

