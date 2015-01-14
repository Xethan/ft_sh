/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:37:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/14 16:11:22 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_env	chdir_me(char *target, t_env var)
{
	char	*tmp;

	if (chdir(target) == -1)
	{
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putendl_fd(target, 2);
	}
	else
	{
		tmp = var.old_pwd;
		var.old_pwd = var.pwd;
		free(tmp);
		var.pwd = ft_strdup(target);
	}
	return (var);
}

void	change_dir(char **arg, t_env var, size_t sz_arg)
{
	if (sz_arg == 1 || ft_strequ(arg[1], "~"))
		var = chdir_me(var.home, var);
	else if (sz_arg == 3)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(arg[1], 2);
	}
	else if (sz_arg >= 4)
		ft_putendl_fd("cd: too many arguments", 2);
	else if (ft_strnequ(arg[1], "~", 1))
		var = chdir_me(ft_strjoin(var.home, arg[1] + 1), var);
	else
	{
		// Check validite directory;
		var = chdir_me(arg[1], var);
		// lstat --> No such file or directory / Is not a directory
	}
	//chdir_me avec message d'erreur
}
