# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 08:32:10 by ruiferna          #+#    #+#              #
#    Updated: 2025/04/30 13:50:45 by ruiferna         ###   ########.fr        #
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
				ft_putendl_fd.c ft_putnbr_fd.c
OBJ			:=	$(SRC:.c=.o)

BSRC		:=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
				ft_lstmap.c
BOBJ		:=	$(BSRC:.c=.o)

CFLAGS		:=	-Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJECTS = $(OBJ) $(BOBJ)
else
	OBJECTS = $(OBJ)
endif

.PHONY:		all bonus clean fclean re

all:		$(NAME)
	
$(NAME):	$(OBJECTS)
	@echo "\033[1;34mCompiling and archiving $@...\033[0m"
	ar -rc $@ $^
	@echo "\033[1;32m$@ created successfully!\033[0m"

bonus:
	@echo "\033[1;33mCompiling bonus objects...\033[0m"
	@make WITH_BONUS=1 all
	@echo "\033[1;32m$@ created successfully!\033[0m"

*.o:		*.c
	@echo "\033[1;36mCompiling $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;31mCleaning object files...\033[0m"
	@rm -f $(OBJ) $(BOBJ)

fclean:		clean
	@echo "\033[1;31mRemoving $@...\033[0m"
	@rm -f $(NAME)

re:			fclean all
	@echo "\033[1;35mRebuilding project...\033[0m"
