#!/usr/bin/env python3
"""Generate a 64x128 sprite texture (2 frames of 64x64 stacked).
Frame 0: green circle (idle)
Frame 1: green circle with red center (active/pulsing)"""

import os

ROOT = '/home/z/my-project/cub3d/assets'

lines = []
lines.append("/* XPM */")
lines.append("/* Sprite texture 64x128 (2 frames stacked). Replace with real asset. */")
lines.append('static char *sprite[] = {')
lines.append('"64 128 3 1",')
lines.append('"  c #000000",')  # transparent (black)
lines.append('"G c #00FF00",')  # green body
lines.append('"R c #FF0000",')  # red accent

import math

for frame in range(2):
    for y in range(64):
        row = ""
        for x in range(64):
            cx = 32
            cy = 32
            dx = x - cx
            dy = y - cy
            dist = math.sqrt(dx*dx + dy*dy)
            if dist > 20:
                row += " "  # transparent outside circle
            elif dist > 14:
                row += "G"  # green ring
            elif frame == 1 and dist < 6:
                row += "R"  # red center on frame 1
            else:
                row += "G"  # green body
        lines.append(f'"{row}",')

# Remove trailing comma from last line
lines[-1] = lines[-1].rstrip(',')
lines.append("};")

content = "\n".join(lines) + "\n"

path = f"{ROOT}/sprite.xpm"
with open(path, 'w') as f:
    f.write(content)
print(f"  wrote {path} ({os.path.getsize(path)} bytes)")
