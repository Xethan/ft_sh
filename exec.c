/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/01 17:30:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

int		check_access(char *full_path)
{
	char	*bin_path;
	int		i;
	int		ret;
	t_stat	st;
	t_stat	st2;

	i = 0;
	ret = 1;
	while (full_path[i])
		i++;
	while (full_path[i] != '/' && i != 0)
		i--;
	bin_path = ft_strndup(full_path, i);
	if (i != 0 && stat(bin_path, &st) == -1)
		ret = -1;
	else if (i != 0 && access(bin_path, R_OK) == -1)
		ret = -2;
	else if (stat(full_path, &st2) == -1)
		ret = -1;
	else if (S_ISREG(st2.st_mode) == 0 || access(full_path, X_OK) == -1)
		ret = -2;
	free(bin_path);
	return (ret);
}

t_arg	*do_redir(t_arg *plist)
{
	int		fd;

	while (plist && plist->redir && ft_strequ(plist->redir, "|") == 0)
	{
		if (ft_strequ(plist->redir, ">") == 1)
			fd = open(plist->arg[0], O_CREAT | O_RDWR | O_TRUNC);
		else if (ft_strequ(plist->redir, ">>") == 1)
			fd = open(plist->arg[0], O_CREAT | O_RDWR | O_APPEND);
		if (fd == -1)
		{
			ft_putendl("Open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		plist = plist->next;
	}
	return (plist);
}

int		exec_cmd(t_arg *plist, int old_pdes[2])
{
	pid_t	father;
	int		new_pdes[2];

	if (plist->next)
		pipe(new_pdes);
	father = fork();
	if (father == 0)
	{
		//plist = do_redir(plist);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
			close(new_pdes[WRITE_END]);
		}
		if (old_pdes != NULL)
		{
			close(old_pdes[WRITE_END]);
			dup2(old_pdes[READ_END], STDIN_FILENO);
			close(old_pdes[READ_END]);
		}
		ft_putendl(plist->arg[0]);
		execve(plist->arg[0], plist->arg, g_env);
		ft_putstr_fd("ft_sh1: exec format error: ", 2);
		ft_putendl_fd(plist->arg[0], 2);
		exit(EXIT_FAILURE);
	}
	if (father > 0)
	{
		if (plist->next != NULL)
			exec_cmd(plist->next, new_pdes);
		else
			wait(NULL);
	}
	return (1);
}

char	*ft_strtrijoin(char *s1, char *s2, char *s3)
{
	char	*tmp;

	tmp = ft_strjoin(s2, s3);
	s1 = ft_strjoin(s1, tmp);
	free(tmp);
	return (s1);
}

int		try_regular_path(char **path, size_t nb_path, char **arg)
{
	size_t	i;
	char	*cmd;
	int		ret;

	if (arg[0][0] != '.' && arg[0][0] != '/')
	{
		if (nb_path == 0)
			return (0);
		i = 0;
		while (i != nb_path)
		{
			cmd = ft_strtrijoin(path[i], "/", arg[0]);
			ret = check_access(cmd);
			if (ret == 1)
			{
				free(arg[0]);
				arg[0] = ft_strdup(cmd);
			}
			free(cmd);
			if (ret == 1 || ret == -2)
				return (ret);
			i++;
		}
		return (0);
	}
	else
		return (check_access(arg[0]));
}

void	try_all_path(t_arg *blist)
{
	t_arg	*plist;
	char	**path;
	size_t	nb_path;
	int		ret;

	path = ft_sizesplit(find_env("PATH"), ':', &nb_path);
	plist = blist;
	while (plist != NULL)
	{
		if (plist->redir == NULL || ft_strequ(plist->redir, "|") == 1)
		{
			ret = try_regular_path(path, nb_path, plist->arg);
			if (ret == -2)
				ft_putstr_fd("ft_sh1: permission denied: ", 2);
			if (ret == 0)
				ft_putstr_fd("ft_sh1: command not found: ", 2);
			if (ret == -1)
				ft_putstr_fd("ft_sh1: no such file or directory: ", 2);
			if (ret != 1)
				ft_putendl_fd(plist->arg[0], 2);
		}
		plist = plist->next;
	}
	exec_cmd(blist, NULL);
	ft_freetab(path, nb_path);
}
