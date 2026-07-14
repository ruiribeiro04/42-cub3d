#!/usr/bin/env python3
"""Generate Makefile with mandatory/bonus split and texture assets."""

import os

ROOT = '/home/z/my-project/cub3d'

# =====================================================================
#  Makefile with mandatory/bonus split
# =====================================================================
MAKEFILE = r"""# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#              #
#    Updated: 2025/07/11 16:00:00 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ NAMES & PATHS ================================= #

NAME            := cub3D

LIBFT_DIR       := libft
LIBFT           := $(LIBFT_DIR)/libft.a

FTPRINTF_DIR    := ft_printf
FTPRINTF        := $(FTPRINTF_DIR)/libftprintf.a

MLX_DIR         := minilibx-linux
MLX_LIB         := $(MLX_DIR)/libmlx_Linux.a

INCS_DIR        := includes

# ============================ COMPILATION =================================== #

CC              := cc
CFLAGS          := -Wall -Wextra -Werror
IFLAGS          := -I$(INCS_DIR) -Isrc/parser -Isrc/graphics \
                   -Isrc/raycaster -Isrc/player -Isrc/bonus \
                   -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(MLX_DIR)

PARSER_LDFLAGS  := -L$(LIBFT_DIR) -lft \
                   -L$(FTPRINTF_DIR) -lftprintf

LDFLAGS         := $(PARSER_LDFLAGS) -L$(MLX_DIR) -lmlx \
                   -lm -lXext -lX11

# ============================ SOURCES ======================================= #

# Mandatory sources (compiled by both `make` and `make bonus`)
PARSER_SRCS     := src/parser/parser.c \
                   src/parser/parser_io.c \
                   src/parser/parser_textures.c \
                   src/parser/parser_colors.c \
                   src/parser/parser_map.c \
                   src/parser/parser_map_helpers.c \
                   src/parser/parser_spawn.c \
                   src/parser/parser_flood_fill.c \
                   src/parser/parser_validate.c

ERROR_SRCS      := src/error/error.c
UTILS_SRCS      := src/utils/free_utils.c

GNL_SRCS        := get_next_line/get_next_line.c \
                   get_next_line/get_next_line_utils.c

GRAPHICS_SRCS   := src/graphics/init.c \
                   src/graphics/cleanup.c \
                   src/graphics/textures.c \
                   src/graphics/pixel.c \
                   src/graphics/hooks_common.c \
                   src/graphics/hooks.c \
                   src/graphics/run.c

RAYCASTER_SRCS  := src/raycaster/raycaster.c \
                   src/raycaster/raycaster_draw.c

PLAYER_SRCS     := src/player/player.c \
                   src/player/player_move.c \
                   src/player/player_apply.c

MAIN_SRCS       := src/main.c

# Files replaced by _bonus counterparts in bonus build
BONUS_EXCLUDE   := src/graphics/hooks.c src/graphics/run.c \
                   src/parser/parser_utils.c

# Bonus-only sources (compiled only by `make bonus`)
BONUS_SRCS      := src/bonus/minimap.c \
                   src/bonus/doors.c \
                   src/bonus/mouse.c \
                   src/bonus/sprites.c \
                   src/bonus/sprites_draw.c \
                   src/bonus/sprite_anim.c \
                   src/bonus/sprites_init.c \
                   src/parser/parser_utils_bonus.c \
                   src/parser/parser_sprite.c \
                   src/parser/parser_sprite_collect.c \
                   src/parser/parser_doors.c \
                   src/graphics/init_sprites.c \
                   src/graphics/hooks_bonus.c \
                   src/graphics/run_bonus.c

# Mandatory utils (always compiled, not excluded)
PARSER_UTILS_MAND := src/parser/parser_utils.c

# ============================ OBJECT RULES ================================== #

# For mandatory build
MANDATORY_SRCS  := $(PARSER_SRCS) $(PARSER_UTILS_MAND) $(ERROR_SRCS) \
                   $(UTILS_SRCS) $(GNL_SRCS) $(GRAPHICS_SRCS) \
                   $(RAYCASTER_SRCS) $(PLAYER_SRCS) $(MAIN_SRCS)

# For bonus build: mandatory minus excluded + bonus
BONUS_ALL_SRCS  := $(filter-out $(BONUS_EXCLUDE),$(MANDATORY_SRCS)) \
                   $(BONUS_SRCS)

MANDATORY_OBJS  := $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS      := $(BONUS_ALL_SRCS:.c=.o)

# ============================ TARGETS ======================================= #

.PHONY:         all clean fclean re bonus test test_run norm

# Default: build mandatory only
all:            $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(NAME)

$(NAME):        $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(MANDATORY_OBJS)
	@echo "\033[1;34mLinking $(NAME) (mandatory)...\033[0m"
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LDFLAGS) -o $(NAME)

# Bonus: clean mandatory objects, rebuild with bonus sources
bonus:          $(LIBFT) $(FTPRINTF) $(MLX_LIB)
	@echo "\033[1;33mBuilding bonus...\033[0m"
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	@$(MAKE) BONUS_BUILD=1 $(NAME)_bonus

$(NAME)_bonus:  $(BONUS_OBJS)
	@echo "\033[1;34mLinking $(NAME) (bonus)...\033[0m"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)
	@rm -f $(NAME)_bonus

# ----- pattern rule for project sources ------------------------------------- #
%.o:            %.c
	@echo "\033[1;36mCompiling $<...\033[0m"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# ----- sub-library builds --------------------------------------------------- #
$(LIBFT):
	@echo "\033[1;33mBuilding libft...\033[0m"
	$(MAKE) -C $(LIBFT_DIR)

$(FTPRINTF):
	@echo "\033[1;33mBuilding ft_printf...\033[0m"
	$(MAKE) -C $(FTPRINTF_DIR)

$(MLX_LIB):
	@echo "\033[1;33mBuilding minilibx-linux...\033[0m"
	cd $(MLX_DIR) && ./configure || true
	@test -f $(MLX_LIB) && echo "minilibx OK" || \
	    (echo "minilibx build failed"; exit 1)

# ----- tests ---------------------------------------------------------------- #
test:           $(LIBFT) $(FTPRINTF) test_parser

TEST_OBJS       := $(PARSER_SRCS:.c=.o) $(ERROR_SRCS:.c=.o) \
                   $(UTILS_SRCS:.c=.o) $(GNL_SRCS:.c=.o)

test_parser:    tests/test_parser.c $(TEST_OBJS)
	@echo "\033[1;34mBuilding test_parser...\033[0m"
	$(CC) $(CFLAGS) $(IFLAGS) tests/test_parser.c \
	    $(TEST_OBJS) $(PARSER_LDFLAGS) -lm -o tests/test_parser

test_run:       test
	@echo "\033[1;35mRunning parser tests...\033[0m"
	./tests/test_parser
	@echo "\033[1;35mRunning shell-based map tests...\033[0m"
	./tests/run_parser_tests.sh

# ----- norm ----------------------------------------------------------------- #
norm:
	norminette $(INCS_DIR) src

# ----- cleanup -------------------------------------------------------------- #
clean:
	@echo "\033[1;31mCleaning project objects...\033[0m"
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	rm -f tests/test_parser
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) clean 2>/dev/null || true

fclean:         clean
	@echo "\033[1;31mRemoving binaries...\033[0m"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) fclean 2>/dev/null || true

re:             fclean all
	@echo "\033[1;35mRebuilt everything.\033[0m"
"""

path = f'{ROOT}/Makefile'
with open(path, 'w') as f:
    f.write(MAKEFILE)
print(f"  wrote {path}")

# =====================================================================
#  assets/door.xpm — 64x64 brown door
# =====================================================================
lines = ["/* XPM */", "/* Door texture 64x64. */", 'static char *door[] = {',
         '"64 64 4 1",', '"  c #000000",', '"W c #8B4513",',
         '"D c #654321",', '"H c #FFD700",']

for y in range(64):
    row = ""
    for x in range(64):
        if x == 0 or x == 63 or y == 0 or y == 63:
            row += "W"
        elif x < 4 or x > 59 or y < 4 or y > 59:
            row += "D"
        elif (x == 31 or x == 32) and y > 30:
            row += "D"  # door seam
        elif y == 30 and x > 27 and x < 36:
            row += "H"  # door handle
        elif x == 8 or x == 55:
            row += "D"  # panel edges
        elif y == 8 or y == 27 or y == 50:
            row += "D"  # panel edges
        else:
            row += "W"
    if y < 63:
        lines.append(f'"{row}",')
    else:
        lines.append(f'"{row}"')
lines.append("};")

with open(f'{ROOT}/assets/door.xpm', 'w') as f:
    f.write("\n".join(lines) + "\n")
print("  wrote assets/door.xpm")

# =====================================================================
#  assets/sprite01.xpm — 64x64 green circle (frame 1)
# =====================================================================
import math

for frame, (name, has_red) in enumerate(
    [("sprite01.xpm", False), ("sprite02.xpm", True)], 1):
    lines = [f"/* XPM */", f"/* Sprite frame {frame} 64x64. */",
             f'static char *sprite0{frame}[] = {{',
             '"64 64 3 1",', '"  c #000000",', '"G c #00FF00",',
             '"R c #FF0000",']
    for y in range(64):
        row = ""
        for x in range(64):
            dx = x - 32
            dy = y - 32
            dist = math.sqrt(dx*dx + dy*dy)
            if dist > 22:
                row += " "
            elif dist > 18:
                row += "G"
            elif has_red and dist < 8:
                row += "R"
            else:
                row += "G"
        if y < 63:
            lines.append(f'"{row}",')
        else:
            lines.append(f'"{row}"')
    lines.append("};")
    with open(f'{ROOT}/assets/{name}', 'w') as f:
        f.write("\n".join(lines) + "\n")
    print(f"  wrote assets/{name}")

# =====================================================================
#  Test maps
# =====================================================================

# valid_sprites.cub — uses SP base path (sprite01.xpm, sprite02.xpm)
with open(f'{ROOT}/maps/valid_sprites.cub', 'w') as f:
    f.write("""NO ./assets/north.xpm
SO ./assets/south.xpm
WE ./assets/west.xpm
EA ./assets/east.xpm
SP ./assets/sprite
F 220,100,0
C 225,30,0
1111111111
1000200001
1000000001
1000000001
1000000001
1000000001
1000N00001
1111111111
""")

# valid_doors.cub — uses DO door texture
with open(f'{ROOT}/maps/valid_doors.cub', 'w') as f:
    f.write("""NO ./assets/north.xpm
SO ./assets/south.xpm
WE ./assets/west.xpm
EA ./assets/east.xpm
DO ./assets/door.xpm
F 220,100,0
C 225,30,0
1111111111
1000000D01
1000000001
1000000001
1000000001
1000000001
1000N00001
1111111111
""")

# valid_all_bonus.cub — sprites + doors
with open(f'{ROOT}/maps/valid_all_bonus.cub', 'w') as f:
    f.write("""NO ./assets/north.xpm
SO ./assets/south.xpm
WE ./assets/west.xpm
EA ./assets/east.xpm
SP ./assets/sprite
DO ./assets/door.xpm
F 220,100,0
C 225,30,0
111111111111
100020000D01
100000000001
100000200001
100000000001
100000000001
1000N0000001
111111111111
""")

# Remove old sprite.xpm (single file, no longer used)
old_sprite = f'{ROOT}/assets/sprite.xpm'
if os.path.exists(old_sprite):
    os.remove(old_sprite)
    print("  removed old assets/sprite.xpm")

print("\n=== Part 4 done (Makefile + textures + maps) ===")
