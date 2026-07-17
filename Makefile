# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 19:00:00 by ruiferna          #+#    #+#              #
#    Updated: 2026/07/17 11:40:45 by ruiferna         ###   ########.fr        #
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
IFLAGS          := -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(MLX_DIR)


LDFLAGS         := -L$(LIBFT_DIR) -lft \
                   -L$(FTPRINTF_DIR) -lftprintf \
                   -L$(MLX_DIR) -lmlx \
                   -lm -lXext -lX11


# ============================ SOURCES ======================================= #


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


BONUS_ONLY_SRCS := src/bonus/minimap.c \
                   src/bonus/doors.c \
                   src/bonus/mouse.c \
                   src/bonus/sprites.c \
                   src/bonus/sprites_draw.c \
                   src/bonus/sprite_anim.c \
                   src/bonus/sprites_init.c


BONUS_EXCLUDE   := src/graphics/hooks.c src/graphics/run.c \
                   src/graphics/init_sprites.c \
                   src/parser/parser_utils.c


BONUS_REPLACE   := src/graphics/hooks_bonus.c \
                   src/graphics/run_bonus.c \
                   src/graphics/init_sprites_bonus.c \
                   src/parser/parser_utils_bonus.c


MANDATORY_OBJS  := $(ALL_SRCS:.c=.o)


BONUS_SRCS      := $(filter-out $(BONUS_EXCLUDE),$(ALL_SRCS)) \
                   $(BONUS_ONLY_SRCS) \
                   $(BONUS_REPLACE)
BONUS_OBJS      := $(BONUS_SRCS:.c=.o)


# ============================ TARGETS ======================================= #


.PHONY:         all clean fclean re bonus clean_bonus_objs norm


all:            $(NAME)


$(NAME):        $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(MANDATORY_OBJS)
	@echo "\033[1;34mLinking $(NAME) (mandatory)...\033[0m"
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LDFLAGS) -o $(NAME)


bonus:          $(BONUS_NAME)


$(BONUS_NAME):  $(LIBFT) $(FTPRINTF) $(MLX_LIB) $(BONUS_OBJS)
	@echo "\033[1;34mLinking $(BONUS_NAME) (bonus)...\033[0m"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)


clean_bonus_objs:
	@rm -f $(BONUS_OBJS)


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


norm:
	norminette $(INCS_DIR) src libs/get_next_line


clean:
	@echo "\033[1;31mCleaning project objects...\033[0m"
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) clean 2>/dev/null || true


fclean:         clean
	@echo "\033[1;31mRemoving binaries...\033[0m"
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean 2>/dev/null || true
	$(MAKE) -C $(FTPRINTF_DIR) fclean 2>/dev/null || true


re:             fclean all