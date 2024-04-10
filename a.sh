#!/bin/bash
DIR="$(pwd)/src"
EXTENSION=".c"
DEFAULT_FILE="main"

comp() {
    local filename=${1:-$DEFAULT_FILE}

    local file_path="$DIR/$filename$EXTENSION"
    if [ ! -f "$file_path" ]; then
        echo "comp: File $file_path does not exist."
        return 1
    fi

    gcc "$file_path" -o "$DIR/$filename.exe" -Wall

    if [ $? -eq 0 ]; then
        echo "comp: Compilation successful. Running the program..."
        "$DIR/$filename.exe"
    else
        echo "comp: Compilation failed."
    fi
}

cl() {
    find $DIR -type f \( -name "*.out" -o -name "*.exe"\) -exec rm {} \;
    echo "cl: Cleaned up the directory."
}
