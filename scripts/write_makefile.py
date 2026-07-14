#!/usr/bin/env python3
"""Generate the cub3D Makefile with mandatory/bonus split."""
import os

MAKEFILE = """# **************************************************************************** #
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
PARSER_INCS_DIR := src/parser

# ============================ COMPILATION =================================== #

CC              := cc
CFLAGS          := -Wall -Wextra -Werror
IFLAGS          := -I$(INCS_DIR) -I$(PARSER_INCS_DIR) \\
                   -Isrc/graphics -Isrc/raycaster -Isrc/player -Isrc/bonus \\
                   -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(MLX_DIR)

PARSER_LDFLAGS  := -L$(LIBFT_DIR) -lft \\
                   -L$(FTPRINTF_DIR) -lftprintf

LDFLAGS         := $(PARSER_LDFLAGS) -L$(MLX_DIR) -lmlx \\
                   -lm -lXext -lX11

# ============================ SOURCES ======================================= #

PARSER_SRCS     := src/parser/parser.c \\
                   src/parser/parser_io.c \\
                   src/parser/parser_textures.c \\
                   src/parser/parser_colors.c \\
                   src/parser/parser_map.c \\
                   src/parser/parser_map_helpers.c \\
                   src/parser/parser_spawn.c \\
                   src/parser/parser_sprite.c \\
                   src/parser/parser_sprite_collect.c \\
                   src/parser/parser_doors.c \\
                   src/parser/parser_flood_fill.c \\
                   src/parser/parser_validate.c

ERROR_SRCS      := src/error/error.c
UTILS_SRCS      := src/utils/free_utils.c

GNL_SRCS        := get_next_line/get_next_line.c \\
                   get_next_line/get_next_line_utils.c

GRAPHICS_SRCS   := src/graphics/init.c \\
                   src/graphics/init_sprites.c \\
                   src/graphics/cleanup.c \\
                   src/graphics/textures.c \\
                   src/graphics/pixel.c

RAYCASTER_SRCS  := src/raycaster/raycaster.c \\
                   src/raycaster/raycaster_draw.c

PLAYER_SRCS     := src/player/player.c \\
                   src/player/player_move.c \\
                   src/player/player_apply.c

MAIN_SRCS       := src/main.c

# Files shared by both builds but whose impl differs between mandatory
# and bonus are selected via the BONUS variable below.

# ============================ BONUS TOGGLE ================================== #

ifeq ($(BONUS),1)
SWAP_SRCS       := src/graphics/hooks_bonus.c \\
                   src/graphics/run_bonus.c \\
                   src/parser/parser_utils_bonus.c
BONUS_RUNTIME   := src/bonus/minimap.c \\
                   src/bonus/doors.c \\
                   src/bonus/mouse.c \\
                   src/bonus/sprites.c \\
                   src/bonus/sprites_draw.c \\
                   src/bonus/sprite_anim.c
else
SWAP_SRCS       := src/graphics/hooks.c \\
                   src/graphics/run.c \\
                   src/parser/parser_utils.c
BONUS_RUNTIME   :=
endif

# sprites_init.c is shared (loader code; harmless in mandatory build)
SHARED_BONUS    := src/bonus/sprites_init.c

PROJECT_SRCS    := $(PARSER_SRCS) $(ERROR_SRCS) $(UTILS_SRCS) \\
                   $(GNL_SRCS) $(GRAPHICS_SRCS) $(RAYCASTER_SRCS) \\
                   $(PLAYER_SRCS) $(MAIN_SRCS) $(SWAP_SRCS) \\
                   $(BONUS_RUNTIME) $(SHARED_BONUS)
PROJECT_OBJS    := $(PROJECT_SRCS:.c=.o)

# ============================ TARGETS ======================================= #

.PHONY:         all clean fclean re bonus test test_run norm

all:            $(LIBFT) $(FTPRINTF) $(NAME)

$(NAME):        $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(PROJECT_OBJS)
\t@echo "\\033[1;34mLinking $(NAME)...\\033[0m"
\t$(CC) $(CFLAGS) $(PROJECT_OBJS) $(LDFLAGS) -o $(NAME)

%.o:            %.c
\t@echo "\\033[1;36mCompiling $<...\\033[0m"
\t$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
\t@echo "\\033[1;33mBuilding libft...\\033[0m"
\t$(MAKE) -C $(LIBFT_DIR)

$(FTPRINTF):
\t@echo "\\033[1;33mBuilding ft_printf...\\033[0m"
\t$(MAKE) -C $(FTPRINTF_DIR)

$(MLX_LIB):
\t@echo "\\033[1;33mBuilding minilibx-linux...\\033[0m"
\tcd $(MLX_DIR) && ./configure || true
\t@test -f $(MLX_LIB) && echo "minilibx OK" || \\
\t    (echo "minilibx build failed"; exit 1)

# Bonus: do a fresh compile with BONUS=1 (so _bonus swap files are used).
bonus:
\t@echo "\\033[1;32mBuilding bonus (BONUS=1)...\\033[0m"
\t@$(MAKE) clean
\t@$(MAKE) BONUS=1 all

test:           $(LIBFT) $(FTPRINTF) test_parser

# Exclude main.o, graphics, raycaster, player, bonus from parser test build
TEST_OBJS       := $(PARSER_SRCS:.c=.o) $(ERROR_SRCS:.c=.o) $(UTILS_SRCS:.c=.o) \\
                   $(GNL_SRCS:.c=.o) src/parser/parser_utils.o

test_parser:    tests/test_parser.c $(TEST_OBJS)
\t@echo "\\033[1;34mBuilding test_parser...\\033[0m"
\t$(CC) $(CFLAGS) $(IFLAGS) tests/test_parser.c \\
\t    $(TEST_OBJS) $(PARSER_LDFLAGS) -lm -o tests/test_parser

test_run:       test
\t@echo "\\033[1;35mRunning parser tests...\\033[0m"
\t./tests/test_parser
\t@echo "\\033[1;35mRunning shell-based map tests...\\033[0m"
\t./tests/run_parser_tests.sh

norm:
\tnorminette $(INCS_DIR) src

clean:
\t@echo "\\033[1;31mCleaning project objects...\\033[0m"
\trm -f $(PROJECT_OBJS) $(TEST_OBJS)
\trm -f tests/test_parser
\t$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
\t$(MAKE) -C $(FTPRINTF_DIR) clean 2>/dev/null || true

fclean:         clean
\t@echo "\\033[1;31mRemoving binaries...\\033[0m"
\trm -f $(NAME)
\t$(MAKE) -C $(LIBFT_DIR) fclean 2>/dev/null || true
\t$(MAKE) -C $(FTPRINTF_DIR) fclean 2>/dev/null || true

re:             fclean all
\t@echo "\\033[1;35mRebuilt everything.\\033[0m"
"""

# Convert \t escape sequences to actual tabs
content = MAKEFILE.replace('\\t', '\t').replace('\\\\', '\\')

path = '/home/z/my-project/cub3d/Makefile'
with open(path, 'w') as f:
    f.write(content)
print(f"Wrote {path} ({len(content)} bytes)")

# Verify tabs
with open(path, 'r') as f:
    for i, line in enumerate(f, 1):
        if line.startswith('\t'):
            print(f"  Line {i}: starts with TAB (good)")
            if i > 90:
                break
