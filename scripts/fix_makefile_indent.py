#!/usr/bin/env python3
"""Fix Makefile indentation: convert leading 16 spaces to a tab in recipe lines."""
import sys

path = sys.argv[1]
with open(path, 'r') as f:
    lines = f.readlines()

# In this Makefile, recipe lines (and only recipe lines) start with 16 spaces.
# Variable continuations also use 16 spaces but they're inside a variable assignment
# (lines ending with '\'). We need to be careful.
#
# Strategy: track whether we're "inside a recipe" (just saw a target: deps line
# without a recipe yet, or already in a recipe). Convert leading 16-space prefix
# to a tab when inside a recipe.

out = []
in_recipe = False
for line in lines:
    raw = line.rstrip('\n')
    # Detect target line: "target: deps" (no leading whitespace, has ':')
    stripped = raw.lstrip()
    if stripped and not raw[0].isspace() and ':' in raw and not '=' in raw.split(':')[0]:
        # Could be a target. Check next line for recipe.
        in_recipe = True
        out.append(raw + '\n')
        continue
    # Detect end of recipe: a non-empty line that doesn't start with whitespace
    # AND isn't a comment, variable, or empty.
    if in_recipe:
        if raw and not raw[0].isspace():
            # Could be a new target, variable, or section comment.
            if ':' in raw and not '=' in raw.split(':')[0] and not raw.startswith('#'):
                in_recipe = True
            else:
                in_recipe = False
            out.append(raw + '\n')
            continue
        # It's an indented line. If it starts with exactly 16 spaces, convert to tab.
        if raw.startswith('                '):
            out.append('\t' + raw[16:] + '\n')
        elif raw.startswith('\t'):
            out.append(raw + '\n')
        else:
            out.append(raw + '\n')
    else:
        out.append(raw + '\n')

with open(path, 'w') as f:
    f.writelines(out)
print(f"Fixed {path}")
