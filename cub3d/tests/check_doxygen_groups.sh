#!/bin/bash
# check_doxygen_groups.sh - Verify every public function has an @ingroup marker
# Exit 0 if all present, 1 with missing functions listed otherwise.

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
FAIL=0

check_dir() {
    local dir="$1"
    for f in $(find "$dir" -name '*.c' ! -path '*/libft/*' ! -path '*/minilibx/*' | sort); do
        # Extract non-static function names (skip lines with 'static')
        funcs=$(grep -v '^[[:space:]]*static' "$f" | grep -oP '(?:int|void|char|t_\w+|unsigned \w+)\s+\Kft_[a-z_]+(?=\s*\()' 2>/dev/null)
        for fname in $funcs; do
            # Check if this specific function has @ingroup near its definition
            if ! grep -B5 "^[[:space:]]*\(int\|void\|char\|t_[a-z_]*\|unsigned [a-z_]*\) $fname" "$f" | grep -q '@ingroup'; then
                echo "FAIL: $f (function $fname) has no @ingroup"
                FAIL=1
            fi
        done
    done
}

check_dir "$ROOT/srcs"
check_dir "$ROOT/srcs_bonus"

if [ "$FAIL" -eq 0 ]; then
    echo "OK: All public functions have @ingroup markers."
    exit 0
else
    echo "FAIL: Some functions are missing @ingroup markers."
    exit 1
fi
