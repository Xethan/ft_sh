/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/31 17:24:55 by ncolliau         ###   ########.fr       */
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

# define WRITE_END	1
# define READ_END	0

typedef struct stat	t_stat;

typedef struct		s_arg
{
	char			**arg;
	size_t			sz_arg;
	char			*redir;
	struct	s_arg	*next;
}					t_arg;

int					built_in(char **cmd, size_t sz_arg);

void				treat_cmd(char **arg, size_t sz_arg);

int					check_access(char *bin_path);
//int					exec_cmd(t_arg *plist, int test);
void				try_all_path(t_arg *plist);

t_arg				*lstnew(char **arg, size_t sz_arg, char *redir);
void				lst_creat_after(t_arg *list, char **arg, size_t sz_arg, char *redir);
void				lstdel(t_arg **begin_list);

void				up_shlvl(void);
void				ft_env(void);
void				ft_setenv(char *name, char *value);
void				ft_unsetenv(char **to_del, size_t sz_arg);

void				chdir_me(char *target);
void				change_dir(char **arg, size_t sz_arg);

void				dup_env(char **env, int ac, char **av);
void				free_env(void);
size_t				len_env(void);
char				*find_env(char *str);
int					nb_env(char *to_find);

#endif
