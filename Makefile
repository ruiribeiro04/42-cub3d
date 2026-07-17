# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#              #
#    Updated: 2025/07/17 15:00:00 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ NAMES & PATHS ================================= #

NAME            := cub3D
BONUS_NAME      := cub3D_bonus

LIBFT_DIR       := libs/libft
LIBFT           := $(LIBFT_DIR)/libft.a

FTPRINTF_DIR    := libs/ft_printf
FTPRINTF        := $(FTPRINTF_DIR)/libftprintf.a

MLX_DIR         := libs/minilibx-linux
MLX_LIB         := $(MLX_DIR)/libmlx_Linux.a

INCS_DIR        := includes

# ============================ COMPILATION =================================== #

CC              := cc
CFLAGS          := -Wall -Wextra -Werror
DEPFLAGS        := -MMD -MP
IFLAGS          := -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(MLX_DIR)

PARSER_LDFLAGS  := -L$(LIBFT_DIR) -lft \
		   -L$(FTPRINTF_DIR) -lftprintf

LDFLAGS         := $(PARSER_LDFLAGS) -L$(MLX_DIR) -lmlx \
		   -lm -lXext -lX11

# ============================ SOURCES ======================================= #

# All project sources (compiled in both mandatory and bonus)
ALL_SRCS        := src/parser/parser.c \
		   src/parser/parser_utils.c \
		   src/parser/parser_utils_common.c \
		   src/parser/parser_io.c \
		   src/parser/parser_tabs.c \
		   src/parser/parser_lines.c \
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
		   src/utils/shared_helpers.c \
		   libs/get_next_line/get_next_line.c \
		   libs/get_next_line/get_next_line_utils.c \
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
		   src/main.c

# Bonus-only sources (not compiled into the mandatory binary)
BONUS_ONLY_SRCS := src/bonus/minimap.c \
		   src/bonus/doors.c \
		   src/bonus/mouse.c \
		   src/bonus/sprites.c \
		   src/bonus/sprites_draw.c \
		   src/bonus/sprite_anim.c \
		   src/bonus/sprites_init.c

# Files replaced by _bonus counterparts in bonus build
BONUS_EXCLUDE   := src/graphics/hooks.c src/graphics/run.c \
		   src/graphics/init_sprites.c \
		   src/parser/parser_utils.c

# Bonus replacement files
BONUS_REPLACE   := src/graphics/hooks_bonus.c \
		   src/graphics/run_bonus.c \
		   src/graphics/init_sprites_bonus.c \
		   src/parser/parser_utils_bonus.c

# Mandatory objects
MANDATORY_OBJS  := $(ALL_SRCS:.c=.o)

# Bonus objects: all minus excluded plus replacements plus bonus-only
BONUS_SRCS      := $(filter-out $(BONUS_EXCLUDE),$(ALL_SRCS)) \
		   $(BONUS_ONLY_SRCS) \
		   $(BONUS_REPLACE)
BONUS_OBJS      := $(BONUS_SRCS:.c=.o)

# Dependency files
DEPFILES        := $(MANDATORY_OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

# ============================ TARGETS ======================================= #

.PHONY:         all clean fclean re bonus norm clean_bonus_objs

all:            $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(NAME)

$(NAME):        | $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(MANDATORY_OBJS)
	@echo "\033[1;34mLinking $(NAME) (mandatory)...\033[0m"
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LDFLAGS) -o $(NAME)

# Bonus: separate binary with bonus sources
bonus:          $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(BONUS_NAME)

$(BONUS_NAME):  $(BONUS_OBJS)
	@echo "\033[1;34mLinking $(BONUS_NAME) (bonus)...\033[0m"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)

# Clean bonus objects only (without removing mandatory objects)
clean_bonus_objs:
	@rm -f $(BONUS_OBJS) $(BONUS_OBJS:.o=.d)

%.o:            %.c
	@echo "\033[1;36mCompiling $<...\033[0m"
	$(CC) $(CFLAGS) $(DEPFLAGS) $(IFLAGS) -c $< -o $@

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

norm:
	norminette $(INCS_DIR) src libs/get_next_line

clean:
	@echo "\033[1;31mCleaning project objects...\033[0m"
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS) $(DEPFILES)
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) clean 2>/dev/null || true

fclean:         clean
	@echo "\033[1;31mRemoving binaries...\033[0m"
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) fclean 2>/dev/null || true

re:             fclean all
	@echo "\033[1;35mRebuilt everything.\033[0m"

# Include dependency files
-include $(DEPFILES)