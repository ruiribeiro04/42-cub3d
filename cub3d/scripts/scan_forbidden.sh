#!/usr/bin/env bash
# ===========================================================================
# scan_forbidden.sh — Detect forbidden libc functions in srcs_bonus/
#
# Per subject Ch. V "External Function", the following are the ONLY allowed
# external functions: open, close, read, write, printf (via ft_printf),
# malloc, free, perror, strerror, exit, gettimeofday, all of <math.h>,
# and all of MiniLibX plus the in-tree libft.
#
# Bare libc calls like strcpy, strdup, atoi, memcpy, etc. are forbidden.
# This script uses grep -rnw (word boundary) to detect them.
# Note: ft_printf, ft_strlen, ft_strchr etc. are NOT matched because the
# ft_ prefix breaks the word boundary before the libc function name.
# ===========================================================================
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/forbidden-functions.log"

{
    echo "=== scan_forbidden.sh run on $(date -Iseconds) ==="
    cd "$ROOT" || exit 2
    grep -rnw 'printf\|scanf\|strtok\|strdup\|strcpy\|strcat\|strncpy\|strncat\|strlcpy\|strlcat\|memcpy\|memmove\|system\|atoi\|getenv\|usleep\|sleep\|signal' srcs_bonus/ 2>/dev/null || true
} > "$OUT" 2>&1

if [ -s "$OUT" ] && grep -q 'srcs_bonus/' "$OUT"; then
    echo "FAIL: forbidden function(s) found. See $OUT"
    exit 1
fi
echo "OK: 0 forbidden functions found in srcs_bonus/"
exit 0
