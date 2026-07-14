#!/usr/bin/env python3
"""Generate valid 64x64 XPM textures for testing.
These are placeholders — the user will provide real assets."""

import os

ROOT = '/home/z/my-project/cub3d/assets'

def make_xpm(name, color, label):
    """Generate a 64x64 XPM with a solid color and a simple pattern."""
    lines = []
    lines.append("/* XPM */")
    lines.append(f"/* {label} texture (64x64). Replace with real asset. */")
    lines.append(f"static char *{name}[] = {{")
    lines.append('"64 64 2 1",')
    lines.append('"  c #000000",')
    lines.append(f'"X c {color}",')
    for y in range(64):
        row = ""
        for x in range(64):
            # Create a simple brick-like pattern
            if (y % 16 < 2) or (x % 16 < 2 and (y // 8) % 2 == 0) or (x % 16 < 2 and (y // 8) % 2 == 1 and (x // 16) % 2 == 1):
                row += " "
            else:
                row += "X"
        if y < 63:
            lines.append(f'"{row}",')
        else:
            lines.append(f'"{row}"')
    lines.append("};")
    return "\n".join(lines) + "\n"

textures = [
    ("north", "#CC4444", "North wall (red brick)"),
    ("south", "#44CC44", "South wall (green brick)"),
    ("west",  "#4444CC", "West wall (blue brick)"),
    ("east",  "#CCCC44", "East wall (yellow brick)"),
]

for name, color, label in textures:
    path = f"{ROOT}/{name}.xpm"
    with open(path, 'w') as f:
        f.write(make_xpm(name, color, label))
    print(f"  wrote {path} ({os.path.getsize(path)} bytes)")

print("Textures generated.")
