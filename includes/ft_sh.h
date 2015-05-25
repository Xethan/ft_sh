/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:56:19 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/24 16:35:21 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
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

enum	e_put
{
	PIPE, FD, INPUT
};

typedef struct		s_tools
{
	char			*pipe;
	char			*input;
	int				fd_in;
	int				fd_out;
	enum e_put		in;
	enum e_put		out;
}					t_tools;

typedef struct		s_arg
{
	char			*cmd;
	char			**arg;
	size_t			sz_arg;
	char			**left_fd;
	char			**right_fd;
	char			**stop;
	struct s_arg	*next;
}					t_arg;

int					launch_cmds(t_arg *plist, int old_pdes[2], char **path);

int					ft_env(t_arg *plist, int new_pdes[2], char **path);
int					ft_setenv(char **arg);
void				ft_setenv_name_value(char *name, char *value);
void				ft_unsetenv(char **to_del, size_t sz_arg);

int					open_it(char *file, int redir);
char				*get_input(char **stop);
char				*get_pipe(int old_pdes[2]);
void				put_in_stdin(char *input);

int					recurse(t_arg *plist, int pdes[2], char **path, int ret);
void				child_things(t_arg *plist, int pdes[2], t_tools tools);
int					fork_exec(t_arg *plist, int pdes[2], t_tools tools);
t_tools				init_tools(char *pipe, char *input, int fd_in, int fd_out);

int					fd_to_fd(t_arg *plist);
int					fd_to_output(t_arg *plist, int new_pdes[2]);
int					input_to_fd(t_arg *plist, char *line);
int					input_to_output(t_arg *plist, char *line, int new_pdes[2]);
int					stdin_to_fd(t_arg *plist, char *pipe);
int					stdin_to_output(t_arg *plist, int new_pdes[2], char *pipe);

t_arg				*cmd_to_list(char *cmd);
int					is_redir(char *s);
char				*replace_tabs(char *line);
char				**tilde_and_dollar(char **cmd, size_t sz_cmd);

void				chdir_me(char *target);
void				change_dir(char **arg);

char				**dup_env(char **env);
void				free_env(void);
size_t				len_env(void);
char				*find_env(char *str);
int					nb_env(char *to_find);

int					check_error_pipe(char *line);
int					check_error(char *line);
void				access_error(int error, char *name);

int					disp_prompt(void);
int					get_exit_status(int status, char *prog);
void				sighandler(int signal);
void				up_shlvl(void);
void				lstdel(t_arg **begin_list);

int					built_in(t_arg *plist, int new_pdes[2], char **path);
int					cmds(t_arg *plist, int new_pdes[2], char *input, char *pip);
int					check_access(char *full_path);
int					find_path(char **path, char *cmd, char **pathed_cmd);

#endif
