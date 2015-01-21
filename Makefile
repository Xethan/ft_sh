# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/14 11:02:20 by ncolliau          #+#    #+#              #
#    Updated: 2015/01/21 11:18:38 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell1

OBJ = ft_sh1.o env.o cd.o get_next_line.o env_tools.o exec.o

PATH_INCLUDES = includes/

INCLUDES_NAME = ft_sh1.h get_next_line.h libft.h

INCLUDES = $(addprefix $(PATH_INCLUDES),$(INCLUDES_NAME))

FLAGS = -Wall -Wextra -Werror

.PHONY: make, all, $(NAME), libft/libft.a, clean, fclean, re, norme

all : $(NAME)

$(NAME) : $(OBJ) libft/libft.a
			gcc $(FLAGS) -o $(NAME) $(OBJ) libft/libft.a

$(OBJ): %.o: %.c $(INCLUDES)
			gcc $(FLAGS) -I $(PATH_INCLUDES) -c $< -o $@

libft/libft.a :
			make -C libft/

clean :
			@rm -f $(OBJ)
			@echo "clean done"

fclean : clean
			rm -f $(NAME)
			make -C libft/ fclean

re : fclean all

norme :
			norminette $(OBJ:.o=.c) $(INCLUDES)
			make -C libft/ norme
