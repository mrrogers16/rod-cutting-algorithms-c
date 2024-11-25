#!/bin/bash

# Variables
EXECUTABLE="project3"
MAKEFILE="Makefile"

# Step 1: Compile the project using the Makefile with C99 flag
echo "Compiling the project with C99 standard..."
if [ -f "$MAKEFILE" ]; then
    make CFLAGS="-std=c99 -Wall -Wextra -g"
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Exiting."
        exit 1
    fi
else
    echo "Makefile not found. Exiting."
    exit 1
fi

# Step 2: Check if the executable was created
if [ ! -f "$EXECUTABLE" ]; then
    echo "Executable '$EXECUTABLE' not found after compilation. Exiting."
    exit 1
fi

# Step 3: Check if input arguments are provided
if [ $# -lt 2 ]; then
    echo "Usage: $0 <number_of_rods> <rod_lengths...>"
    exit 1
fi

# Step 4: Run the program with the provided input
echo "Running the program..."
./$EXECUTABLE "$@"

# End of script
