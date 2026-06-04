# ---------------------- Variables ---------------------------------------------

# Executables
NAME          = cub3D
NAME_BONUS    = cub3D_bonus

# Commands
CC            = cc
RM            = rm -f

# Directories
SRC_DIR       = srcs
SRC_DIR_BONUS = srcs_bonus
OBJ_DIR       = objs
OBJ_DIR_BONUS = objs_bonus
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
SRCS_BONUS    = $(shell find $(SRC_DIR_BONUS) -name "*.c")

# OBJs
OBJS          = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS    = $(patsubst $(SRC_DIR_BONUS)/%.c, $(OBJ_DIR_BONUS)/%.o, $(SRCS_BONUS))

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

 $(NAME_BONUS): $(LIBFT) $(MLX_LIB) $(OBJS_BONUS)
	@echo ""
	@echo "$(YELLOW)Linking Object Files to make $(NAME_BONUS)...$(RESET)"
	$(CC) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)Done! Execute ./$(NAME_BONUS)$(RESET)"

bonus: $(NAME_BONUS)

# ---------------------- Norminette ---------------------------------------------
norminette: SHELL := /bin/bash
norminette: .SHELLFLAGS := -o pipefail -c
norminette:
	@echo "$(CYAN)Running norminette on srcs/, srcs_bonus/, includes/...$(RESET)"
	@norminette srcs/ srcs_bonus/ includes/ 2>&1 | tee norminette.log
	@echo "$(GREEN)Norminette OK! See norminette.log for evidence.$(RESET)"

lint:
	@echo "$(CYAN)Running forbidden-function scan...$(RESET)"
	@bash scripts/scan_forbidden.sh
	@echo "$(CYAN)Checking for unprefixed libft calls in srcs_bonus/...$(RESET)"
	@OUTPUT=$$(grep -rnw 'strlen\|strchr\|strrchr\|strstr\|strncmp\|memset\|calloc\|atoi' srcs_bonus/ 2>/dev/null | grep -v 'libs/libft/'); \
	if [ -n "$$OUTPUT" ]; then \
		echo "$$OUTPUT" | tee forbidden-functions.log; \
		echo "$(RED)FAIL: unprefixed libft calls found$(RESET)"; \
		exit 1; \
	fi
	@echo "$(GREEN)Lint OK!$(RESET)"

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

 $(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling Bonus $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------- Cleaning ----------------------------------------------
clean:
	@echo "$(CYAN)Cleaning Object Files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_DIR_BONUS)
	@if [ -d "$(MLX_DIR)" ]; then make -sC $(MLX_DIR) clean 2>/dev/null || true; fi
	@make -sC $(LIBFT_DIR) clean
	@make docs_clean
	@echo "$(GREEN)Done!$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables and MiniLibX...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS) valgrind-out.txt valgrind-bonus-out.txt
	@$(RM) -r $(MLX_DIR)
	@make -sC $(LIBFT_DIR) fclean
	@echo "$(GREEN)Done!$(RESET)"

re: fclean all

# ---------------------- Debugging & Testing -----------------------------------
debug: CFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += -fsanitize=address
debug: re

debug_bonus: CFLAGS += $(DEBUG_FLAGS)
debug_bonus: LDFLAGS += -fsanitize=address
debug_bonus: bonus

# make valgrind ARGS="maps/mapa.cub"
valgrind: CFLAGS += -g
valgrind: $(NAME)
	@echo "$(CYAN)Running Valgrind on $(NAME) with args: $(ARGS)...$(RESET)"
		valgrind --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=mlx.supp \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(NAME) $(ARGS)
		@echo "$(GREEN)Valgrind finished! Check valgrind-out.txt$(RESET)"

# make valgrind_all - run valgrind on every mandatory map
valgrind_all: CFLAGS += -g
valgrind_all: $(NAME)
	@mkdir -p valgrind-maps
	@SUMMARY=valgrind-maps/summary.txt; \
	rm -f $$SUMMARY; \
	FAIL=0; \
	MAP_COUNT=0; \
	for map in maps/mandatory/*.cub; do \
		[ -f "$$map" ] || continue; \
		MAP_COUNT=$$((MAP_COUNT + 1)); \
		name=$$(basename $$map .cub); \
		log=valgrind-maps/$$name.log; \
		echo "$(CYAN)Valgrind on $$map...$(RESET)"; \
		timeout 5 valgrind --leak-check=full --show-leak-kinds=all \
			--suppressions=mlx.supp \
			--log-file=$$log \
			./$(NAME) $$map > /dev/null 2>&1; \
		DEF=$$(grep 'definitely lost:' $$log | awk '{print $$4}'); \
		DEF=$${DEF:-0}; \
		REA=$$(grep 'still reachable:' $$log | awk '{print $$4}'); \
		REA=$${REA:-0}; \
		echo "$$name: definitely_lost=$$DEF still_reachable=$$REA" >> $$SUMMARY; \
		if [ "$$DEF" != "0" ] || [ "$$REA" != "0" ]; then \
			echo "$(RED)$$name: leak detected$(RESET)"; \
			FAIL=1; \
		else \
			echo "$(GREEN)$$name: OK$(RESET)"; \
		fi; \
	done; \
	if [ $$MAP_COUNT -eq 0 ]; then \
		echo "$(RED)No .cub files found in maps/mandatory/$(RESET)"; \
		exit 1; \
	fi; \
	if [ $$FAIL = 1 ]; then \
		echo "$(RED)FAIL: at least one map has non-MLX leaks$(RESET)"; \
		exit 1; \
	fi; \
	echo "$(GREEN)OK: all maps clean$(RESET)"

# make valgrind_bonus ARGS="maps/mapa_bonus.cub"
valgrind_bonus: CFLAGS += -g
valgrind_bonus: $(NAME_BONUS)
	@echo "$(CYAN)Running Valgrind on $(NAME_BONUS) with args: $(ARGS)...$(RESET)"
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--suppressions=mlx.supp \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-bonus-out.txt \
		./$(NAME_BONUS) $(ARGS)
	@echo "$(GREEN)Valgrind finished! Check valgrind-bonus-out.txt$(RESET)"

# ---------------------- Documentation ----------------------------------------
docs:
	@echo "$(CYAN)Generating Doxygen documentation...$(RESET)"
	@cd .. && doxygen Doxyfile
	@echo "$(GREEN)Documentation generated! Open ../doxygen/doxygen_docs/index.html$(RESET)"

docs_clean:
	@echo "$(CYAN)Cleaning Doxygen documentation...$(RESET)"
	@$(RM) -r $(DOXYGEN_DIR)
	@echo "$(GREEN)Documentation cleaned!$(RESET)"

docs_check: docs
	@echo "$(CYAN)Checking Doxygen warnings...$(RESET)"
	@bash tests/check_doxygen_warnings.sh

# ---------------------- Testing -----------------------------------------------
test: all
	@echo "$(CYAN)Running test suite...$(RESET)"
	@./tests/run_tests.sh

test_parser: $(LIBFT) $(MLX_LIB) $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
	@echo "$(CYAN)Compiling and running parser tests...$(RESET)"
	@gcc -o test_parser tests/test_parser.c tests/test_framework.c \
		-I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) \
		$(filter-out $(OBJ_DIR)/main.o,$(OBJS)) \
		$(LDFLAGS)
	@./test_parser

test_parser_exhaustive: $(LIBFT) $(MLX_LIB) $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
	@echo "$(CYAN)Compiling and running EXHAUSTIVE parser tests...$(RESET)"
	@gcc -o test_parser_exhaustive tests/test_parser_exhaustive.c tests/test_framework.c \
		-I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) \
		$(filter-out $(OBJ_DIR)/main.o,$(OBJS)) \
		$(LDFLAGS)
	@./test_parser_exhaustive

test_memory: all
	@echo "$(CYAN)Running memory leak tests...$(RESET)"
	@./tests/run_tests.sh memory

test_integration: $(LIBFT) $(MLX_LIB) $(filter-out $(OBJ_DIR)/main.o,$(OBJS))
	@echo "$(CYAN)Compiling and running integration tests...$(RESET)"
	@gcc -o test_integration tests/test_integration.c tests/test_framework.c \
		-I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR) \
		$(filter-out $(OBJ_DIR)/main.o,$(OBJS)) \
		$(LDFLAGS)
	@./test_integration

test_all: test_parser test_parser_exhaustive test_integration test_memory
	@echo "$(GREEN)All test suites executed!$(RESET)"

test_clean:
	@echo "$(CYAN)Cleaning test files...$(RESET)"
	@$(RM) test_parser test_parser_exhaustive test_memory test_integration
	@$(RM) -r tests/maps_invalid

.PHONY: all bonus clean fclean re debug debug_bonus valgrind valgrind_bonus valgrind_all docs docs_clean docs_check test test_parser test_parser_exhaustive test_memory test_integration test_all test_clean norminette lint
