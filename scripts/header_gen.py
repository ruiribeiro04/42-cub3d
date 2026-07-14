#!/usr/bin/env python3
"""Regenerate ALL cub3D parser files with correct 80-char headers."""

import os

ROOT = '/home/z/my-project/cub3d'

def header(name):
    """Generate an 80-char-wide 42 header. Login/mail/dates are fixed."""
    login = 'ruiferna'
    mail = 'ruiferna@student.42porto.com'
    created = '2025/07/10 19:00:00'
    updated = '2025/07/11 10:00:00'

    # Each line must be exactly 80 chars.
    # Line 4: "/*   " (5) + name (51) + ":+:..." (24) = 80
    line4_name = name.ljust(51)
    # Line 6: "/*   By: " (9) + "login <mail>" + spaces + "+#..." (28) = 80
    #   "login <mail>" + spaces = 43 chars
    by_content = f"{login} <{mail}>"
    line6_by = by_content.ljust(43)
    # Line 8: "/*   Created: " (14) + "date by login" + spaces + "#+#..." (25) = 80
    #   "date by login" + spaces = 41 chars
    created_content = f"{created} by {login}"
    line8_created = created_content.ljust(41)
    # Line 9: "/*   Updated: " (14) + "date by login" + spaces + "###..." (26) = 80
    #   "date by login" + spaces = 40 chars
    updated_content = f"{updated} by {login}"
    line9_updated = updated_content.ljust(40)

    return (
        "/* ************************************************************************** */\n"
        "/*                                                                            */\n"
        "/*                                                        :::      ::::::::   */\n"
        f"/*   {line4_name}:+:      :+:    :+:   */\n"
        "/*                                                    +:+ +:+         +:+     */\n"
        f"/*   By: {line6_by}+#+  +:+       +#+        */\n"
        "/*                                                +#+#+#+#+#+   +#+           */\n"
        f"/*   Created: {line8_created}#+#    #+#             */\n"
        f"/*   Updated: {line9_updated}###   ########.fr       */\n"
        "/*                                                                            */\n"
        "/* ************************************************************************** */\n"
    )

def write_file(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w') as f:
        f.write(content)

# Verify header is exactly 80 chars per line
h = header("test.c")
for i, line in enumerate(h.split('\n'), 1):
    if line and len(line) != 80:
        print(f"WARN: header line {i} is {len(line)} chars (expected 80): {line!r}")

print("Header generator ready.")
