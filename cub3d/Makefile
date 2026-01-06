# ---------------------- Variables ---------------------------------------------

# Executables
NAME          = cub3d
NAME_BONUS    = cub3d_bonus

# Commands
CC            = cc
RM            = rm -f

# Directories
SRC_DIR       = srcs
OBJ_DIR       = objs
INC_DIR       = includes
MLX_DIR       = minilibx

# Compiling Flags
CFLAGS        = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)

# MLX Linking
LDFLAGS       = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# SRCs Find
SRCS          = $(shell find $(SRC_DIR) -name "*.c")

# OBJs
OBJS          = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# MiniLibX Library
MLX_LIB       = $(MLX_DIR)/libmlx.a

# Colors
GREEN         = \033[0;32m
RED           = \033[0;31m
YELLOW        = \033[0;33m
CYAN          = \033[0;36m
RESET         = \033[0m

# ---------------------- Default -----------------------------------------------

all: $(NAME)

# ---------------------- Linking -----------------------------------------------

$(NAME): $(MLX_LIB) $(OBJS)
	@echo ""
	@echo "$(YELLOW)Linking Object Files to make $(NAME)...$(RESET)"
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Done! Execute ./$(NAME)$(RESET)"

bonus: all

# ---------------------- MiniLibX ----------------------------------------------

# Download MLX - O diretório como target garante que só baixa uma vez
$(MLX_DIR):
	@echo "$(CYAN)Downloading MiniLibX...$(RESET)"
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)
	@echo "$(GREEN)MiniLibX downloaded!$(RESET)"

# Compile MLX - Order-only prerequisite (|) para o diretório
$(MLX_LIB): | $(MLX_DIR)
	@echo "$(CYAN)Compiling MiniLibX...$(RESET)"
	@make -sC $(MLX_DIR)
	@echo "$(GREEN)MiniLibX compiled!$(RESET)"

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
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)Done!$(RESET)"

# Remove tudo incluindo a MLX baixada
ffclean: fclean
	@echo "$(RED)Removing MiniLibX...$(RESET)"
	@$(RM) -r $(MLX_DIR)
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean ffclean re