# ---------------------- Variables ---------------------------------------------

# Executables
NAME          = cub3D
NAME_BONUS    = cub3D_bonus

# Commands
CC            = cc
RM            = rm -f

# Directories
SRC_DIR       = srcs
OBJ_DIR       = objs
INC_DIR       = includes
MLX_DIR       = minilibx
LIBS_DIR      = libs
LIBFT_DIR     = $(LIBS_DIR)/libft
DOXYGEN_DIR   = ../doxygen

# Compiling Flags
CFLAGS        = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
# MLX Linking
LDFLAGS       = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -L$(LIBFT_DIR) -lft
# Debug Flags
DEBUG_FLAGS = -g -fsanitize=address -fno-omit-frame-pointer



# SRCs Find
SRCS          = $(shell find $(SRC_DIR) -name "*.c")
# OBJs
OBJS          = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# MinilibX Library
MLX_LIB       = $(MLX_DIR)/libmlx.a

# Libft Library
LIBFT         = $(LIBFT_DIR)/libft.a

# Colors
GREEN         = \033[0;32m
RED           = \033[0;31m
YELLOW        = \033[0;33m
CYAN          = \033[0;36m
RESET         = \033[0m

# ---------------------- Default -----------------------------------------------

all: $(NAME)

# ---------------------- Linking -----------------------------------------------

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	@echo ""
	@echo "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

bonus: all

# ---------------------- MiniLibX ----------------------------------------------

$(MLX_DIR):
	@echo "$(CYAN)Downloading MiniLibX...$(RESET)"
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)
	@echo "$(GREEN)MiniLibX downloaded!$(RESET)"

$(MLX_LIB): | $(MLX_DIR)
	@echo "$(CYAN)Compiling MiniLibX...$(RESET)"
	@make -sC $(MLX_DIR)
	@echo "$(GREEN)MiniLibX compiled!$(RESET)"

# ---------------------- Libft -------------------------------------------------

$(LIBFT):
	@echo "$(CYAN)Compiling Libft...$(RESET)"
	@make -sC $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(RESET)"

# ---------------------- Compiling ---------------------------------------------

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------- Cleaning ----------------------------------------------

clean:
	@echo "$(CYAN)Cleaning Object Files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@if [ -d "$(MLX_DIR)" ]; then make -sC $(MLX_DIR) clean 2>/dev/null || true; fi
	@make -sC $(LIBFT_DIR) clean
	@make docs_clean
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables and MiniLibX...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS) valgrind-out.txt
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(RM) -r $(MLX_DIR)
	@make -sC $(LIBFT_DIR) fclean
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

# ---------------------- Debugging & Testing -----------------------------------

debug: CFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += -fsanitize=address
debug: re


# make valgrind ARGS="maps/outro_mapa.cub"

valgrind: CFLAGS += -g
valgrind: $(NAME)
	@echo "$(CYAN)Running Valgrind on $(NAME) with args: $(ARGS)...$(RESET)"
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=valgrind-out.txt \
			 ./$(NAME) $(ARGS)
	@echo "$(GREEN)Valgrind finished! Check valgrind-out.txt$(RESET)"

# ---------------------- Documentation ----------------------------------------

docs:
	@echo "$(CYAN)Generating Doxygen documentation...$(RESET)"
	@cd .. && doxygen Doxyfile
	@echo "$(GREEN)Documentation generated! Open ../doxygen/doxygen_docs/index.html$(RESET)"

docs_clean:
	@echo "$(CYAN)Cleaning Doxygen documentation...$(RESET)"
	@$(RM) -r $(DOXYGEN_DIR)
	@echo "$(GREEN)Documentation cleaned!$(RESET)"

.PHONY: all bonus clean fclean re debug valgrind docs docs_clean
