/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/06 17:00:54 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <stdio.h>

extern char **g_env;

t_arg	*do_redir(t_arg *plist, int *fd_tab)
{
	int		fd;
	t_arg	*tmp;

	plist = plist->next;
	fd = 0; // important
	if (plist && plist->redir && ft_strequ(plist->redir, "|") == 0) // while
	{
		fd = 0;
		if (ft_strequ(plist->redir, ">") == 1)
			fd = open(plist->arg[0], O_CREAT | O_RDWR | O_TRUNC, 0664);
		else if (ft_strequ(plist->redir, ">>") == 1)
			fd = open(plist->arg[0], O_CREAT | O_RDWR | O_APPEND, 0664);
		else if (ft_strequ(plist->redir, "<") == 1)
			fd = open(plist->arg[0], O_RDONLY) * -1;
		if (fd == -1 || fd == 1)
		{
			ft_putstr_fd("Open failed : ", 2);
			ft_putendl_fd(plist->arg[0], 2);
			exit(EXIT_FAILURE);
		}
		tmp = plist;
		plist = plist->next;
		tmp->next = NULL;
		lstdel(&tmp);
	}
	*fd_tab = fd;
	return (plist);
}

void	child(t_arg *plist, int new_pdes[2], int old_pdes[2])
{
	size_t	i;

	i = 0;
	while (i != plist->sz)
	{
		if (plist->fd_tab[i] > 0)
			dup2(plist->fd_tab[i], STDOUT_FILENO);
		if (plist->fd_tab[i] < 0)
			dup2(plist->fd_tab[i] * -1, STDIN_FILENO);
		i++;
		ft_putnbr_nl_fd(i, STDOUT_FILENO);
	}
	if (plist->next)
	{
		close(new_pdes[READ_END]);
		dup2(new_pdes[WRITE_END], STDOUT_FILENO);
	}
	if (old_pdes != NULL)
	{
		close(old_pdes[WRITE_END]);
		dup2(old_pdes[READ_END], STDIN_FILENO);
	}
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
	//plist->next = do_redir(plist, &fd);
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
