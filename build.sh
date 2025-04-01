#!/bin/bash

# Loop through all directories in the current directory
for dir in */; do
    # Remove trailing slash from directory name
    dir_name="${dir%/}"
    
    # Check if test.cpp exists in the directory
    if [[ -f "$dir_name/test.cpp" ]]; then
        echo "Compiling $dir_name/test.cpp..."
        clang++ -std=c++17 -mavx -mavx2 -march=native -Werror -Wextra -Wall "$dir_name/test.cpp" -I./src/ -o "$dir_name/a.out"
        if [[ $? -eq 0 ]]; then
            echo "Compilation successful: $dir_name/a.out"
        else
            echo "Compilation failed for $dir_name/test.cpp"
        fi
    else
        echo "Skipping $dir_name (no test.cpp found)"
    fi
done
