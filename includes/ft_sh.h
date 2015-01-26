/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/26 15:22:31 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>

# define C_NONE		"\033[0m"
# define C_BOLD		"\033[1m"
# define C_BLACK	"\033[30m"
# define C_RED		"\033[31m"
# define C_GREEN	"\033[32m"
# define C_BROWN	"\033[33m"
# define C_BLUE		"\033[34m"
# define C_MAGENTA	"\033[35m"
# define C_CYAN		"\033[36m"
# define C_GRAY		"\033[37m"

typedef struct stat	t_stat;

typedef struct	s_env
{
	char		**path;
	size_t		nb_path;
	char		*home;
	char		*user;
	char		**env;
	size_t		sz;
	char		*pwd;
	char		*old_pwd;
}				t_env;

int				check_access(char *bin_path);
int				exec_cmd(char **arg, char *path);
void			try_all_path(char **arg);

void			up_shlvl(void);
void			ft_env(void);
void			ft_setenv(char *name, char *value);
void			ft_unsetenv(char **to_del, size_t sz_arg);

void			chdir_me(char *target);
void			change_dir(char **arg, size_t sz_arg);

void			dup_env(char **env, int ac, char **av);
void			free_env(void);
size_t			len_env(void);
char			*find_env(char *str);
int				nb_env(char *to_find);

#endif
