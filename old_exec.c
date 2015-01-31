/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/30 15:26:08 by ncolliau         ###   ########.fr       */
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

int		exec_cmd(char **arg, char *path)
{
	pid_t	father;
	char	*cmd;
	int		ret;

	cmd = ft_strjoin(path, arg[0]);
	ret = check_access(cmd);
	if (ret != 1)
	{
		free(cmd);
		return (ret);
	}
	father = fork();
	if (father == 0)
	{
		execve(cmd, arg, g_env);
		ft_putstr_fd("ft_sh1: exec format error: ", 2);
		ft_putendl_fd(arg[0], 2);
		exit(EXIT_FAILURE);
	}
	if (father > 0)
		wait(NULL);
	free(cmd);
	return (1);
}

int		try_regular_path(char **path, size_t nb_path, char **arg)
{
	size_t	i;
	char	*cmd;
	int		ret;

	if (nb_path == 0)
		return (0);
	i = 0;
	while (i != nb_path)
	{
		cmd = ft_strjoin(path[i], "/");
		ret = exec_cmd(arg, cmd);
		free(cmd);
		if (ret == 1 || ret == -2)
			return (ret);
		i++;
	}
	return (0);
}

void	try_all_path(char **arg)
{
	char	**path;
	size_t	nb_path;
	int		ret;

	path = ft_sizesplit(find_env("PATH"), ':', &nb_path);
	if (arg[0][0] != '.' && arg[0][0] != '/')
		ret = try_regular_path(path, nb_path, arg);
	else
		ret = exec_cmd(arg, NULL);
	if (ret == -2)
		ft_putstr_fd("ft_sh1: permission denied: ", 2);
	if (ret == 0)
		ft_putstr_fd("ft_sh1: command not found: ", 2);
	if (ret == -1)
		ft_putstr_fd("ft_sh1: no such file or directory: ", 2);
	if (ret != 1)
		ft_putendl_fd(arg[0], 2);
	ft_freetab(path, nb_path);
}