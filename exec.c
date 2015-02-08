/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/08 16:04:08 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

void	exec_redir(t_arg *plist, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{
		if (fd > 0)
			dup2(fd, STDOUT_FILENO);
		if (fd < 0)
			dup2(fd * -1, STDIN_FILENO);
		/*
		if (ft_strequ(redir, "<<") == 1)
		{
			ret = 1;
			while ((ret = get_next_line(0, &stdin) == 1 && ft_strequ(stdin, end_read)) == 0)
			{
				if (ret == -1)
				{
					bla bla
				}
				tmp = line;
				line = ft_strjoin(line, stdin);
				free(tmp);
			}
		}
		*/
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
	while (++i != plist->sz)
		exec_redir(plist, plist->fd_tab[i]);
	if (old_pdes != NULL)
	{
		close(old_pdes[WRITE_END]);
		dup2(old_pdes[READ_END], STDIN_FILENO);
	}
	if (plist->next)
	{
		close(new_pdes[READ_END]);
		dup2(new_pdes[WRITE_END], STDOUT_FILENO);
	}
	else if (plist->sz != 0)
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
		while (i != plist->sz)
		{
			if (plist->fd_tab != 0)
				close(plist->fd_tab[i]);
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
