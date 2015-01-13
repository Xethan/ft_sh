/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/13 15:34:51 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <signal.h>

# define C_NONE         "\033[0m"
# define C_BOLD         "\033[1m"
# define C_BLACK        "\033[30m"
# define C_RED          "\033[31m"
# define C_GREEN        "\033[32m"
# define C_BROWN        "\033[33m"
# define C_BLUE         "\033[34m"
# define C_MAGENTA      "\033[35m"
# define C_CYAN         "\033[36m"
# define C_GRAY         "\033[37m"

typedef struct	s_env
{
	char		**path;
	int			nb_path;
	char		*home;
	char		*user;
	char		**env;
	int			sz;
}				t_env;

void			ft_env(t_env var);
t_env			ft_setenv(char **arg, t_env var);
t_env			ft_unsetenv(char *to_del, t_env var);

void			change_dir(char **arg, t_env var);

#endif
