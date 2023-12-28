#!/bin/bash

# Save the current directory
current_dir=$(pwd)

# Change directory to the parent directory
cd ..

# Execute the Premake5 command (assuming it's executable and in the correct path)
Scripts/bin/premake5 vs2022

# Return to the original directory
cd "$current_dir"

# Pause (Wait for user input) - optional
read -p "Press Enter to continue..."
