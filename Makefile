# **************************************************************************** #
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

# All project sources (compiled in both mandatory and bonus)
ALL_SRCS        := src/parser/parser.c \
                   src/parser/parser_utils.c \
                   src/parser/parser_io.c \
                   src/parser/parser_textures.c \
                   src/parser/parser_colors.c \
                   src/parser/parser_map.c \
                   src/parser/parser_map_helpers.c \
                   src/parser/parser_spawn.c \
                   src/parser/parser_sprite.c \
                   src/parser/parser_sprite_collect.c \
                   src/parser/parser_doors.c \
                   src/parser/parser_flood_fill.c \
                   src/parser/parser_validate.c \
                   src/error/error.c \
                   src/utils/free_utils.c \
                   get_next_line/get_next_line.c \
                   get_next_line/get_next_line_utils.c \
                   src/graphics/init.c \
                   src/graphics/cleanup.c \
                   src/graphics/textures.c \
                   src/graphics/pixel.c \
                   src/graphics/hooks_common.c \
                   src/graphics/hooks.c \
                   src/graphics/run.c \
                   src/graphics/init_sprites.c \
                   src/raycaster/raycaster.c \
                   src/raycaster/raycaster_clear.c \
                   src/raycaster/raycaster_draw.c \
                   src/player/player.c \
                   src/player/player_move.c \
                   src/player/player_apply.c \
                   src/bonus/minimap.c \
                   src/bonus/doors.c \
                   src/bonus/mouse.c \
                   src/bonus/sprites.c \
                   src/bonus/sprites_draw.c \
                   src/bonus/sprite_anim.c \
                   src/bonus/sprites_init.c \
                   src/main.c

# Files replaced by _bonus counterparts in bonus build
BONUS_EXCLUDE   := src/graphics/hooks.c src/graphics/run.c \
                   src/parser/parser_utils.c

# Bonus replacement files
BONUS_REPLACE   := src/graphics/hooks_bonus.c \
                   src/graphics/run_bonus.c \
                   src/parser/parser_utils_bonus.c

# Mandatory objects
MANDATORY_OBJS  := $(ALL_SRCS:.c=.o)

# Bonus objects: all minus excluded plus replacements
BONUS_SRCS      := $(filter-out $(BONUS_EXCLUDE),$(ALL_SRCS)) \
                   $(BONUS_REPLACE)
BONUS_OBJS      := $(BONUS_SRCS:.c=.o)

# ============================ TARGETS ======================================= #

.PHONY:         all clean fclean re bonus test test_run norm

all:            $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(NAME)

$(NAME):        $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(MANDATORY_OBJS)
	@echo "\033[1;34mLinking $(NAME) (mandatory)...\033[0m"
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LDFLAGS) -o $(NAME)

# Bonus: separate compile with bonus replacements
bonus:          fclean_sub $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(NAME)_bonus_link

$(NAME)_bonus_link: $(BONUS_OBJS)
	@echo "\033[1;34mLinking $(NAME) (bonus)...\033[0m"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(NAME)

fclean_sub:
	@rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

%.o:            %.c
	@echo "\033[1;36mCompiling $<...\033[0m"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

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

TEST_OBJS       := src/parser/parser.o src/parser/parser_io.o \
                   src/parser/parser_textures.o src/parser/parser_colors.o \
                   src/parser/parser_map.o src/parser/parser_map_helpers.o \
                   src/parser/parser_spawn.o src/parser/parser_flood_fill.o \
                   src/parser/parser_validate.o src/parser/parser_utils.o \
                   src/parser/parser_sprite.o src/parser/parser_sprite_collect.o \
                   src/parser/parser_doors.o src/error/error.o \
                   src/utils/free_utils.o \
                   get_next_line/get_next_line.o \
                   get_next_line/get_next_line_utils.o

test_parser:    tests/test_parser.c $(TEST_OBJS)
	@echo "\033[1;34mBuilding test_parser...\033[0m"
	$(CC) $(CFLAGS) $(IFLAGS) tests/test_parser.c \
	    $(TEST_OBJS) $(PARSER_LDFLAGS) -lm -o tests/test_parser

test_run:       test
	@echo "\033[1;35mRunning parser tests...\033[0m"
	./tests/test_parser
	@echo "\033[1;35mRunning shell-based map tests...\033[0m"
	./tests/run_parser_tests.sh

norm:
	norminette $(INCS_DIR) src

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
