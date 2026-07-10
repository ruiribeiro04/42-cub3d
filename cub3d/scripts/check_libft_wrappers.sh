#!/usr/bin/env bash
# ===========================================================================
# check_libft_wrappers.sh — Verify all string/memory ops use ft_ wrappers
#
# Finds every .c under srcs/ and srcs_bonus/ that includes <string.h> or
# <stdlib.h>, then checks that libc string functions (strlen, strchr, etc.)
# are called through libft wrappers (ft_strlen, ft_strchr, etc.).
#
# Allowed libc calls (per subject Ch. V): malloc, free, write, read, open,
# close, exit, printf (via ft_printf), perror, strerror, gettimeofday.
#
# Excludes: libs/libft/ (vendored libft legitimately uses libc),
#           includes/cub3d.h (umbrella header, declares but doesn't call).
# ===========================================================================
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
LOG="$ROOT/libft-wrappers.log"

{
    echo "=== check_libft_wrappers.sh run on $(date -Iseconds) ==="
    cd "$ROOT" || exit 2

    FILES=$(grep -rl '#include.*<string\.h>\|#include.*<stdlib\.h>' srcs/ srcs_bonus/ \
            --exclude-dir=libs --exclude='cub3d.h' 2>/dev/null || true)

    if [ -z "$FILES" ]; then
        echo "OK: no <string.h>/<stdlib.h> includes in srcs/ or srcs_bonus/"
        exit 0
    fi

    FAIL=0
    for f in $FILES; do
        MATCHES=$(grep -nw 'strlen\|strchr\|strrchr\|strstr\|strncmp\|memset\|memcpy\|strdup\|strcpy\|strcat\|strncpy\|strncat\|strcmp\|memcmp\|strlcat\|strlcpy' "$f" 2>/dev/null || true)
        LEAKY=$(echo "$MATCHES" | grep -v 'ft_\(strlen\|strchr\|strrchr\|strstr\|strncmp\|memset\|memcpy\|strdup\|strcpy\|strcat\|strncpy\|strncat\|strcmp\|memcmp\|strlcat\|strlcpy\)' 2>/dev/null || true)
        if [ -n "$LEAKY" ]; then
            echo "FAIL: $f has unprefixed libc call(s):"
            echo "$LEAKY"
            FAIL=1
        fi
    done

    if [ "$FAIL" = "1" ]; then
        echo "=== END: violations found ==="
        exit 1
    fi
    echo "OK: all <string.h>/<stdlib.h>-including files use ft_ wrappers"
} > "$LOG" 2>&1

if grep -q 'violations found' "$LOG" 2>/dev/null; then
    exit 1
fi
exit 0
