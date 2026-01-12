# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 08:32:10 by ruiferna          #+#    #+#              #
#    Updated: 2025/09/16 12:26:58 by ruiferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
SRC			:=	ft_memset.c ft_bzero.c ft_memcpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c\
				ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c\
				ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c\
				ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
				ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c\
				\
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
				ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c\
				ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c
OBJ			:=	$(SRC:.c=.o)

BSRC		:=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
				ft_lstmap.c
BOBJ		:=	$(BSRC:.c=.o)

CFLAGS		:=	-Wall -Wextra -Werror

TPUT := $(shell command -v tput 2>/dev/null || true)
ifneq ($(TPUT),)
	DEF_COLOR := $(shell tput sgr0)
	BLUE := $(shell tput setaf 4)
	GREEN := $(shell tput setaf 2)
	YELLOW := $(shell tput setaf 3)
	MAGENTA := $(shell tput setaf 5)
else
	DEF_COLOR := \033[0m
	BLUE := \033[1;34m
	GREEN := \033[1;32m
	YELLOW := \033[1;33m
	MAGENTA := \033[1;35m
endif
ifdef WITH_BONUS
	OBJECTS = $(OBJ) $(BOBJ)
else
	OBJECTS = $(OBJ)
endif

.PHONY:		all bonus clean fclean re

all:		$(NAME)
	
$(NAME):	$(OBJECTS)
	@printf "%b\n" "$(BLUE)Compiling and archiving $@...$(DEF_COLOR)"
	ar -rc $@ $^
	@printf "%b\n" "$(GREEN)$@ created successfully!$(DEF_COLOR)"

bonus:
	@printf "%b\n" "$(YELLOW)Compiling bonus objects...$(DEF_COLOR)"
	@make WITH_BONUS=1 all
	@printf "%b\n" "$(GREEN)$@ created successfully!$(DEF_COLOR)"

*.o:		*.c
	@printf "%b\n" "$(MAGENTA)Compiling $<...$(DEF_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "%b\n" "$(RED)Cleaning object files...$(DEF_COLOR)"
	@rm -f $(OBJ) $(BOBJ)

fclean:		clean
	@printf "%b\n" "$(RED)Removing $@...$(DEF_COLOR)"
	@rm -f $(NAME)

re:			fclean all
	@printf "%b\n" "$(MAGENTA)Rebuilding project...$(DEF_COLOR)"
