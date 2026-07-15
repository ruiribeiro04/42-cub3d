# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 14:01:57 by ruiferna          #+#    #+#              #
#    Updated: 2025/07/15 14:45:00 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            := libftprintf.a
CC              := cc
CFLAGS          := -Wall -Wextra -Werror
AR              := ar rcs
RM              := rm -f

# Colors
DEF_COLOR       := \033[0;39m
GRAY            := \033[0;90m
RED             := \033[0;91m
GREEN           := \033[0;92m
YELLOW          := \033[0;93m
BLUE            := \033[0;94m
MAGENTA         := \033[0;95m
CYAN            := \033[0;96m
WHITE           := \033[0;97m

# Sources
SRC_FILES       := ft_printf ft_putchar_pf ft_putstr_pf ft_putnbr_u_pf \
                   ft_putnbr_pf ft_putnbr_hex ft_putpointer

SRC             := $(addsuffix .c,$(SRC_FILES))
OBJ             := $(addsuffix .o,$(SRC_FILES))

.PHONY:         all clean fclean re

all:            $(NAME)

$(NAME):        $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

%.o:            %.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

fclean:         clean
	@$(RM) $(NAME)
	@echo "$(CYAN)ft_printf library removed!$(DEF_COLOR)"

re:             fclean all
	@echo "$(GREEN)Rebuilt ft_printf!$(DEF_COLOR)"
