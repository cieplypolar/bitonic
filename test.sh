#!/bin/bash
CHECKER="./bin/checker"
TEST_DIR="./test/"

for TEST_FILE in "${TEST_DIR}"*; do
    if [[ -f "$TEST_FILE" ]]; then
        echo "Testing: $TEST_FILE"
        $CHECKER < "$TEST_FILE"
    fi
done