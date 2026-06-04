#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/cub3D"
FAIL=0

assert_extension_rejection() {
	local map_path="$1"
	local label="$2"
	local output
	output=$(timeout 3 "$BIN" "$map_path" 2>&1)
	local CODE=$?
	if [ "$CODE" = "139" ] || [ "$CODE" = "138" ]; then
		echo "FAIL: $label — segfault (code $CODE)"
		FAIL=1
		return
	fi
	if [ "$CODE" = "0" ]; then
		echo "FAIL: $label — expected non-zero exit, got 0"
		FAIL=1
		return
	fi
	local FIRST5
	FIRST5=$(printf '%s' "$output" | head -c 5)
	if [ "$FIRST5" != "Error" ]; then
		echo "FAIL: $label — stderr does not start with Error — got: $(printf '%s' "$output" | head -c 80)"
		FAIL=1
		return
	fi
	echo "OK: $label — rejected with Error\\n prefix"
}

echo "=== Testing .cub extension rejection ==="

MAP="$ROOT/maps/mandatory/small_square.cub"

TXTMAP=$(mktemp /tmp/test_XXXXXX.txt)
cp "$MAP" "$TXTMAP"
assert_extension_rejection "$TXTMAP" "txt_extension"
rm -f "$TXTMAP"

CUMAP=$(mktemp /tmp/test_XXXXXX.cu)
cp "$MAP" "$CUMAP"
assert_extension_rejection "$CUMAP" "cu_extension"
rm -f "$CUMAP"

MAPMAP=$(mktemp /tmp/test_XXXXXX.map)
cp "$MAP" "$MAPMAP"
assert_extension_rejection "$MAPMAP" "map_extension"
rm -f "$MAPMAP"

NOEXT=$(mktemp /tmp/test_XXXXXX)
cp "$MAP" "$NOEXT"
assert_extension_rejection "$NOEXT" "no_extension"
rm -f "$NOEXT"

UPPERMAP=$(mktemp /tmp/test_XXXXXX.CUB)
cp "$MAP" "$UPPERMAP"
assert_extension_rejection "$UPPERMAP" "uppercase_cub"
rm -f "$UPPERMAP"

echo ""
if [ "$FAIL" = "1" ]; then
	echo "FAIL: some extension-rejection tests failed"
	exit 1
fi
echo "OK: all non-.cub extensions rejected"
exit 0
