#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/cub3D"
MAP="$ROOT/maps/mandatory/small_square.cub"
EVIDENCE="$ROOT/evidence/input_test"
mkdir -p "$EVIDENCE"
command -v xdotool >/dev/null 2>&1 || { echo "SKIP: xdotool not installed"; exit 0; }

echo "=== Spawning $BIN $MAP ==="
"$BIN" "$MAP" > "$EVIDENCE/keyboard.log" 2>&1 &
PID=$!
sleep 2

for KEY in w s a d Left Right; do
	xdotool key --window $(xdotool searchname cub3D | head -1) "$KEY" 2>/dev/null || xdotool key "$KEY"
	sleep 0.2
done

if command -v import >/dev/null 2>&1; then
	import -window root "$EVIDENCE/before_escape.png" 2>/dev/null || true
fi

xdotool key Escape
sleep 1
if kill -0 $PID 2>/dev/null; then
	echo "FAIL: process $PID still alive after Escape"
	kill -9 $PID 2>/dev/null
	exit 1
fi
echo "OK: Escape cleanly exited the process"

echo "=== Testing DESTROY_NOTIFY (window close) ==="
"$BIN" "$MAP" > "$EVIDENCE/windowclose.log" 2>&1 &
PID=$!
sleep 2
if command -v wmctrl >/dev/null 2>&1; then
	wmctrl -c cub3D
else
	WID=$(xdotool searchname cub3D | head -1)
	xdotool windowclose "$WID" 2>/dev/null || true
fi
sleep 1
if kill -0 $PID 2>/dev/null; then
	echo "FAIL: process $PID still alive after window close"
	kill -9 $PID 2>/dev/null
	exit 1
fi
echo "OK: window close cleanly exited the process"
exit 0
