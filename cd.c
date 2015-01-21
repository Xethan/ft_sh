/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:37:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/21 12:44:50 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

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
		ft_setenv("OLDPWD", env("PWD"));
		ft_setenv("PWD", target);
		free(target);
		return ;
	}
	ft_putendl_fd(target, 2);
}

void	change_dir(char **arg, size_t sz_arg)
{
	if (sz_arg == 1 || ft_strequ(arg[1], "~") || ft_strequ(arg[1], "--"))
		chdir_me(env("HOME"));
	else if (ft_strequ(arg[1], "-"))
	{
		ft_putendl(env("OLDPWD"));
		chdir_me(env("OLDPWD"));
	}
	else if (sz_arg == 3)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(arg[1], 2);
	}
	else if (sz_arg >= 4)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (ft_strnequ(arg[1], "~", 1))
		chdir_me(ft_strjoin(env("HOME"), arg[1] + 1));
	else
		chdir_me(arg[1]);
}
