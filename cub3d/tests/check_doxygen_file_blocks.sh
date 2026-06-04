#!/bin/bash
# check_doxygen_file_blocks.sh - Verify every .c file in srcs/ and srcs_bonus/ has a @file block
# Exit 0 if all present, 1 with missing files listed otherwise.

MISSING=0

check_dir() {
    local dir="$1"
    for f in $(find "$dir" -name '*.c' ! -path '*/libft/*' ! -path '*/minilibx/*' | sort); do
        if ! grep -q '@file' "$f"; then
            echo "MISSING @file: $f"
            MISSING=1
        fi
    done
}

check_dir "srcs"
check_dir "srcs_bonus"

if [ "$MISSING" -eq 0 ]; then
    echo "OK: All .c files have @file blocks."
    exit 0
else
    echo "FAIL: Some files are missing @file blocks."
    exit 1
fi
