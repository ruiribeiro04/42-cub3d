#!/usr/bin/env bash
set -u
IMG="$1"
[ -f "$IMG" ] || { echo "FAIL: $IMG not found"; exit 1; }
command -v convert >/dev/null 2>&1 || { echo "SKIP: ImageMagick not installed"; exit 0; }
FLOOR_RGB=$(convert "$IMG" -format "%[fx:int(255*p{(640,540)}.r)],%[fx:int(255*p{(640,540)}.g)],%[fx:int(255*p{(640,540)}.b)]" info: 2>/dev/null)
CEIL_RGB=$(convert "$IMG" -format "%[fx:int(255*p{(640,180)}.r)],%[fx:int(255*p{(640,180)}.g)],%[fx:int(255*p{(640,180)}.b)]" info: 2>/dev/null)
echo "floor=$FLOOR_RGB"
echo "ceiling=$CEIL_RGB"
if [ "$FLOOR_RGB" = "$CEIL_RGB" ]; then
	echo "FAIL: floor and ceiling are the same"
	exit 1
fi
echo "OK: floor and ceiling differ"
