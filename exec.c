/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/13 16:53:19 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

char	*get_stdin(char **stop, size_t nb_stop)
{
	int		ret;
	char	*line;
	char	*stdin;
	char	*tmp;
	size_t	i;

	i = 0;
	line = NULL;
	ret = 1;
	while (i != nb_stop)
	{
		stdin = NULL;
		ft_putstr("> ");
		while ((ret = get_next_line(0, &stdin)) == 1 && ft_strequ(stdin, stop[i]) == 0)
		{
			if (ret == -1)
			{
				ft_putendl_fd("Error GNL", 2);
				exit(EXIT_FAILURE);
			}
			tmp = line;
			line = ft_strtrijoin(line, stdin, "\n");
			free(tmp);
			free(stdin);
			ft_putstr("> ");
		}
		i++;
	}
	return (line);
}

void	read_stdin(t_arg *plist)
{
	pid_t	pid;
	int		pdes[2];
	char	*line;

	line = get_stdin(plist->stop, plist->nb_stop);
	pipe(pdes);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
	}
	if (pid == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		ft_putstr(line);
		free(line);
		close(pdes[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
	close(pdes[READ_END]);
}

void	exec_redir(t_arg *plist, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(plist->arg[0], plist->arg, g_env);
		ft_putstr_fd("ft_sh1: exec format error: ", 2);
		ft_putendl_fd(plist->arg[0], 2);
		exit(EXIT_FAILURE);
	}
}

void	child(t_arg *plist, int new_pdes[2], int old_pdes[2])
{
	size_t	i;

	i = -1;
	if (old_pdes != NULL)
	{
		close(old_pdes[WRITE_END]);
		dup2(old_pdes[READ_END], STDIN_FILENO);
	}
	while (plist->right_fd[i] != -1)
		exec_redir(plist, plist->right_fd[i]);
	if (plist->stop != NULL)
		read_stdin(plist);
	if (plist->next)
	{
		close(new_pdes[READ_END]);
		dup2(new_pdes[WRITE_END], STDOUT_FILENO);
	}
	else if (plist->right_fd[0] != -1)
		exit(EXIT_SUCCESS);
	execve(plist->arg[0], plist->arg, g_env);
	ft_putstr_fd("ft_sh1: exec format error: ", 2);
	ft_putendl_fd(plist->arg[0], 2);
	exit(EXIT_FAILURE);
}

int		exec_cmd(t_arg *plist, int old_pdes[2], char **path, size_t nb_path)
{
	pid_t	pid;
	int		new_pdes[2];
	int		ret;
	size_t	i;

	ret = find_path(path, nb_path, plist->arg);
	access_error(ret, plist->arg[0]);
	if (ret != 1)
		return (-1);
	if (plist->next)
		pipe(new_pdes);
	pid = fork();
	if (pid == 0)
		child(plist, new_pdes, old_pdes);
	if (pid > 0)
	{
		wait(NULL);
		i = 0;
		while (plist->right_fd)
		{
			close(plist->right_fd[i]);
			i++;
		}
		if (plist->next)
			close(new_pdes[WRITE_END]);
		if (old_pdes != NULL)
			close(old_pdes[READ_END]);
		if (plist->next)
			exec_cmd(plist->next, new_pdes, path, nb_path);
	}
	return (1);
}
