/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:37:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/19 17:12:54 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

extern char	**g_env;

void	chdir_me(char *target)
{
	t_stat	st;

	if (stat(target, &st) == -1)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	else if (S_ISDIR(st.st_mode) == 0)
		ft_putstr_fd("cd: not a directory: ", 2);
	else if (S_ISRUSR(st.st_mode) == 0)
		ft_putstr_fd("cd: permission denied: ", 2);
	// if (access(target, R_OK) == -1)
	// {
	// 	if (access(target, W_OK) == -1)
	// 	{
	// 		if (access(target, F_OK) == -1)
	// 			ft_putstr_fd("cd: no such file or directory: ", 2);
	// 		else
	// 			ft_putstr_fd("cd: not a directory: ", 2);
	// 	}
	// 	else
	// 		ft_putstr_fd("cd: permission denied: ", 2);
	// 	ft_putendl_fd(target, 2);
	// }
	else if (chdir(target) == -1)
		(void)target;
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
