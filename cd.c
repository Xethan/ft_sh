/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:37:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/24 13:13:01 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		check_cd_access(char *bin_path)
{
	char	*path;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	while (bin_path[i])
		i++;
	while (bin_path[i] != '/' && i != 0)
		i--;
	path = ft_strndup(bin_path, i);
	if (access(path, F_OK) == -1 && i != 0)
		ret = -1;
	else if (access(path, R_OK) == -1 && i != 0)
		ret = -2;
	else if (access(bin_path, F_OK) == -1)
		ret = -1;
	else if (access(bin_path, R_OK) == -1)
		ret = -2;
	free(path);
	return (ret);
}

void	chdir_me(char *target)
{
	int		ret;

	if (target == NULL)
		return ;
	ret = check_cd_access(target);
	if (ret == -2)
		ft_putstr_fd("cd: permission denied: ", 2);
	else if (ret == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (chdir(target) == -1)
		ft_putstr_fd("cd: not a directory: ", 2);
	else
	{
		target = NULL;
		target = getcwd(target, 0);
		if (find_env("PWD") != NULL)
			ft_setenv_name_value("OLDPWD", find_env("PWD"));
		ft_setenv_name_value("PWD", target);
		free(target);
		return ;
	}
	ft_putendl_fd(target, 2);
}

int		ft_strtablen(char **tab)
{
	int		size;

	size = 0;
	while (tab && tab[size])
		size++;
	return (size);
}

void	change_dir(char **arg)
{
	int		size_arg;

	size_arg = ft_strtablen(arg);
	if (size_arg == 1 || ft_strequ(arg[1], "--"))
		chdir_me(find_env("HOME"));
	else if (ft_strequ(arg[1], "-"))
	{
		if (find_env("OLDPWD") != NULL)
			ft_putendl(find_env("OLDPWD"));
		chdir_me(find_env("OLDPWD"));
	}
	else if (size_arg == 3)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(arg[1], 2);
	}
	else if (size_arg >= 4)
		ft_putendl_fd("cd: too many arguments", 2);
	else
		chdir_me(arg[1]);
}
