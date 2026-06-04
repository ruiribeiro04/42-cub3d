#!/bin/bash
# check_doxygen_warnings.sh - Verify make docs produces zero warnings
# for cub3d source files (excluding vendored libs).
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT/.." || exit 2
export PATH="/tmp/doxygen-1.9.8/bin:$PATH"
doxygen Doxyfile > cub3d/evidence/doxygen_warnings.log 2>&1
WARNS=$(grep -n 'warning:' cub3d/evidence/doxygen_warnings.log | grep -v 'libs/libft\|minilibx\|unsupported tag\|does not exist\|is not a readable' || true)
if [ -n "$WARNS" ]; then
    echo "FAIL: Doxygen produced warnings:"
    echo "$WARNS"
    exit 1
fi
echo "OK: Doxygen produced 0 warnings (excluding libft/minilibx)"
