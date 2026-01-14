#!/bin/bash

# Build the project
make

# Create outputs directory if it doesn't exist
mkdir -p outputs

# Run tests for each .kpl file in tests/
for file in tests/*.kpl; do
    # Extract base name without extension
    base=$(basename "$file" .kpl)
    
    # Run the compiler with input from .kpl and output to outputs/
    #./kplc < "$file" > "outputs/$base" 
    
    # Compare the output with the expected file in tests/
    if diff "outputs/$base" "tests/$base" > /dev/null; then
        echo "$base: PASS"
    else
        echo "$base: FAIL"
        echo "Differences:"
        diff "outputs/$base" "tests/$base"
    fi
done