# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/07 15:24:29 by ncolliau          #+#    #+#              #
#    Updated: 2015/02/23 14:55:12 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ =	ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
		ft_isdigit.o ft_isprint.o ft_isspace.o ft_itoa.o ft_lstadd.o \
		ft_lstnew.o ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o \
		ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_putchar.o \
		ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o \
		ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o ft_strcat.o ft_strchr.o \
		ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strdel.o ft_strdup.o	\
		ft_strequ.o ft_striter.o ft_striteri.o ft_strjoin.o ft_strlcat.o \
		ft_strlen.o ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o \
		ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o \
		ft_strsplit.o ft_strstr.o ft_strsub.o ft_strtrim.o ft_tolower.o \
		ft_toupper.o ft_putlonglong.o ft_longlen.o ft_lstdelone.o ft_lstdel.o \
		ft_lstiter.o ft_lstmap.o ft_nbrlen.o ft_lstlen.o ft_strndup.o \
		ft_strcdup.o ft_strclen.o ft_putnbr_nl.o ft_putnbr_nl_fd.o \
		ft_realloc_str_tab.o ft_sizesplit.o ft_freetab.o ft_strtrijoin.o \
		ft_miniprintf.o ft_miniprintf_fd.o

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, $(NAME), clean, fclean, re, norme

all : $(NAME)

$(NAME) : $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@echo "libft compiled"
		ranlib $(NAME)

$(OBJ): %.o: %.c ../includes/libft.h
		gcc $(FLAGS) -I ../includes -c $< -o $@

clean :
		@rm -f $(OBJ)
		@echo "clean done"

fclean : clean
		rm -f $(NAME)

re : fclean all

norme :
		norminette $(OBJ:.o=.c) ../includes/libft.h
