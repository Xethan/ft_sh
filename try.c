/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 18:50:13 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 17:43:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

void	child_things(t_arg *plist, int pdes[2], t_tools tools)
{
	if (tools.in == PIPE && tools.pipe != NULL)
		put_in_stdin(tools.pipe);
	if (tools.in == INPUT && tools.input != NULL)
		put_in_stdin(tools.input);
	if (tools.in == FD)
		dup2(tools.fd_in, STDIN_FILENO);
	if (tools.out == FD)
		dup2(tools.fd_out, STDOUT_FILENO);
	if (tools.out == PIPE && plist->next)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
	}
}

int		fork_exec(t_arg *plist, char *pathed_cmd, int pdes[2], t_tools tools)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 1;
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("ft_sh: fork failed", 2);
	if (pid > 0)
	{
		wait(&status);
		if (tools.out == PIPE && plist->next)
			close(pdes[WRITE_END]);
		ret = get_exit_status(status, plist->arg[0]);
	}
	if (pid == 0)
	{
		child_things(plist, pdes, tools);
		execve(pathed_cmd, plist->arg, g_env);
		ft_putstr_fd("ft_sh: exec format error: ", 2);
		ft_putendl_fd(plist->arg[0], 2);
		exit(126);
	}
	free(pathed_cmd);
	return (ret);
}

int		exec_it(t_arg *plist, int pdes[2], t_tools tools)
{
	char	**path;
	char	*pathed_cmd;
	int		ret;

	path = ft_strsplit(find_env("PATH"), ':');
	ret = find_path(path, plist->arg[0], &pathed_cmd);
	ft_freetab(path);
	access_error(ret, plist->arg[0]);
	if (ret != 0)
	{
		if (tools.out == PIPE && plist->next)
			close(pdes[WRITE_END]);
		return (ret);
	}
	ret = fork_exec(plist, pathed_cmd, pdes, tools);
	return (ret);
}

t_tools	init_tools(char *pipe, char *input, int fd_in, int fd_out)
{
	t_tools	tools;

	tools.pipe = pipe;
	tools.input = input;
	tools.fd_in = fd_in;
	tools.fd_out = fd_out;
	if (input != NULL)
		tools.in = INPUT;
	else if (fd_in != -1)
		tools.in = FD;
	else
		tools.in = PIPE;
	if (fd_out != -1)
		tools.out = FD;
	else
		tools.out = PIPE;
	return (tools);
}
