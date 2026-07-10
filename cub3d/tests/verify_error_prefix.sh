#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/cub3D"
FAIL=0

assert_error_prefix() {
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
	local BYTE6
	BYTE6=$(printf '%s' "$output" | dd bs=1 count=1 skip=5 2>/dev/null)
	if [ "$BYTE6" != "" ] && [ "$BYTE6" != "
" ]; then
		echo "FAIL: $label — byte 6 is not newline, got: $(printf '%s' "$output" | head -c 10 | od -c | head -1)"
		FAIL=1
		return
	fi
	echo "OK: $label — Error\\n prefix present"
}

echo "=== Testing Error\\n prefix on every error path ==="

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'EOF'
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
EOF
assert_error_prefix "$MAP" "missing_north_texture"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
F 100,100,100
C 225,30,0
111111
100101
101001
1100N1
111111
EOF
assert_error_prefix "$MAP" "duplicate_floor"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0
111111
100101
101001
110001
111111
EOF
assert_error_prefix "$MAP" "no_player"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0
111111
100101
101X01
1100N1
111111
EOF
assert_error_prefix "$MAP" "invalid_char"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
: > "$MAP"
assert_error_prefix "$MAP" "empty_file"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'MEOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/nonexistent.xpm
F 220,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
MEOF
assert_error_prefix "$MAP" "nonexistent_texture_file"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.txt)
cp "$ROOT/maps/mandatory/small_square.cub" "$MAP"
assert_error_prefix "$MAP" "wrong_extension"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX)
cp "$ROOT/maps/mandatory/small_square.cub" "$MAP"
assert_error_prefix "$MAP" "no_extension"
rm -f "$MAP"

MAP=$(mktemp /tmp/test_XXXXXX.cub)
cat > "$MAP" << 'EOF'
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 256,100,0
C 225,30,0
111111
100101
101001
1100N1
111111
EOF
assert_error_prefix "$MAP" "color_out_of_range"
rm -f "$MAP"

echo ""
if [ "$FAIL" = "1" ]; then
	echo "FAIL: some error-path tests failed"
	exit 1
fi
echo "OK: all error paths produce Error\\n prefix"
exit 0
