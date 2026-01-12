# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 22:08:52 by ruiferna          #+#    #+#              #
#    Updated: 2025/09/16 12:25:05 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a

# Compiler and flags
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f

# Directories
LIBFT_DIR	:= 42_libft
PRINTF_DIR	:= 42_ft_printf
GNL_DIR		:= 42_get_next_line

TPUT := $(shell command -v tput 2>/dev/null || true)
ifneq ($(TPUT),)
	DEF_COLOR := $(shell tput sgr0)
	GREEN := $(shell tput setaf 2)
 	BLUE := $(shell tput setaf 4)
 	CYAN := $(shell tput setaf 6)
 	YELLOW := $(shell tput setaf 3)
 	RED := $(shell tput setaf 1)
else
 	DEF_COLOR := \033[0;39m
 	GREEN := \033[0;92m
 	BLUE := \033[0;94m
 	CYAN := \033[0;96m
 	YELLOW := \033[0;93m
 	RED := \033[0;91m
endif

# LIBFT sources
LIBFT_SRC	:= ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
			   ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
			   ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
			   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
			   ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

# LIBFT bonus sources  
LIBFT_BONUS	:= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			   ft_lstmap.c

# FT_PRINTF sources
PRINTF_SRC	:= ft_printf.c ft_putchar_pf.c ft_putstr_pf.c ft_putnbr_u_pf.c \
			   ft_putnbr_pf.c ft_putnbr_hex.c ft_putpointer.c

# GET_NEXT_LINE sources
GNL_SRC		:= get_next_line.c get_next_line_utils.c

# GET_NEXT_LINE bonus sources
GNL_BONUS	:= get_next_line_bonus.c get_next_line_utils_bonus.c

# Add directory prefixes to source files
LIBFT_SRCS	:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRC))
LIBFT_BSRCS	:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_BONUS))
PRINTF_SRCS	:= $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRC))
GNL_SRCS	:= $(addprefix $(GNL_DIR)/, $(GNL_SRC))
GNL_BSRCS	:= $(addprefix $(GNL_DIR)/, $(GNL_BONUS))

# Object files
LIBFT_OBJS	:= $(LIBFT_SRCS:.c=.o)
LIBFT_BOBJS	:= $(LIBFT_BSRCS:.c=.o)
PRINTF_OBJS	:= $(PRINTF_SRCS:.c=.o)
GNL_OBJS	:= $(GNL_SRCS:.c=.o)
GNL_BOBJS	:= $(GNL_BSRCS:.c=.o)

# Default objects (without bonus)
OBJECTS		:= $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

# All objects including bonus
ifdef WITH_BONUS
	OBJECTS += $(LIBFT_BOBJS) $(GNL_BOBJS)
endif

# Include paths
INCLUDES	:= -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "%b\n" "$(BLUE)Creating merged libft.a library...$(DEF_COLOR)"
	@$(AR) $(NAME) $(OBJECTS)
	@printf "%b\n" "$(GREEN)✅ libft.a created successfully with libft + ft_printf + get_next_line!$(DEF_COLOR)"

bonus:
	@printf "%b\n" "$(YELLOW)Compiling with bonus functions...$(DEF_COLOR)"
	@$(MAKE) WITH_BONUS=1 all

# Compilation rules for each directory
$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	@printf "%b\n" "$(CYAN)Compiling libft: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
	@printf "%b\n" "$(CYAN)Compiling ft_printf: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@printf "%b\n" "$(CYAN)Compiling get_next_line: $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -DBUFFER_SIZE=42 -c $< -o $@

clean:
	@printf "%b\n" "$(RED)Cleaning object files...$(DEF_COLOR)"
	@$(RM) $(LIBFT_OBJS) $(LIBFT_BOBJS) $(PRINTF_OBJS) $(GNL_OBJS) $(GNL_BOBJS)

fclean: clean
	@printf "%b\n" "$(RED)Removing libft.a...$(DEF_COLOR)"
	@$(RM) $(NAME)

re: fclean all
	@printf "%b\n" "$(GREEN)Project rebuilt successfully!$(DEF_COLOR)"