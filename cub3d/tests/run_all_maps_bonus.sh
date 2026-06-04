#!/usr/bin/env bash
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/cub3D_bonus"
MAP_DIR="$ROOT/maps/bonus"
EVIDENCE="$ROOT/evidence/bonus-maps"
mkdir -p "$EVIDENCE"
rm -f "$EVIDENCE"/*.log 2>/dev/null
SUMMARY="$EVIDENCE/../bonus-maps.log"
: > "$SUMMARY"
FAIL=0
for map in "$MAP_DIR"/*.cub; do
	NAME=$(basename "$map" .cub)
	timeout 3 "$BIN" "$map" > "$EVIDENCE/$NAME.log" 2>&1
	CODE=$?
	HEAD=$(head -c 200 "$EVIDENCE/$NAME.log" | tr -d '\n' | head -c 200)
	echo "$NAME: exit=$CODE first200=$HEAD" >> "$SUMMARY"
	if [ "$CODE" = "139" ] || [ "$CODE" = "138" ]; then
		echo "FAIL: $NAME segfaulted (code $CODE)" >&2
		FAIL=1
	fi
done
if [ "$FAIL" = "1" ]; then
	echo "FAIL: at least one map crashed. See $SUMMARY"
	exit 1
fi
echo "OK: all $(ls "$MAP_DIR"/*.cub | wc -l) maps ran without crash. See $SUMMARY"
