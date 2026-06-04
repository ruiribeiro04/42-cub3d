#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT" || exit 2
FAIL=0
M1=$(grep -rnP 'while\s*\([^)]*\+\+[^)]*\)' srcs/ srcs_bonus/ 2>/dev/null || true)
M2=$(grep -rnP 'while\s*\([^)]*=[^=][^)]*\+\+[^)]*\)' srcs/ srcs_bonus/ 2>/dev/null || true)
M3=$(grep -rnP 'while\s*\([^)]*=\s*i\s*\+\s*1[^)]*\)' srcs/ srcs_bonus/ 2>/dev/null || true)
if [ -n "$M1" ]; then
	echo "FAIL: hidden-for #1 (increment in while condition):"
	echo "$M1"
	FAIL=1
fi
if [ -n "$M2" ]; then
	echo "FAIL: hidden-for #2 (assignment + increment in while condition):"
	echo "$M2"
	FAIL=1
fi
if [ -n "$M3" ]; then
	echo "FAIL: hidden-for #3 (i = i + 1 in while condition):"
	echo "$M3"
	FAIL=1
fi
if [ "$FAIL" = "0" ]; then
	echo "OK: no hidden-for while loops in srcs/ or srcs_bonus/"
fi
exit $FAIL
