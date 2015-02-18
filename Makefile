# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/14 11:02:20 by ncolliau          #+#    #+#              #
#    Updated: 2015/02/18 16:13:01 by ncolliau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_minishell2

OBJ =	main.o env.o cd.o get_next_line.o env_tools.o treat_cmd.o \
		arg_list.o access.o cmd_tools.o exec_tools.o exec_redir.o \
		set_unset_env.o

PATH_INCLUDES = includes/

INCLUDES_NAME = ft_sh.h get_next_line.h libft.h

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

