/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:37:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/12 16:21:13 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	change_dir(char **arg, t_env var)
{
	if (!arg[1] || ft_strequ(arg[1], "~"))
		chdir(var.home);
	else if (ft_strnequ(arg[1], "~", 1))
			chdir(ft_strjoin(var.home, arg[1] + 1));
	else if (arg[1] && arg[2])
		ft_putendl_fd("cd: too many arguments", 2);
	else
	{
		// Check validite directory;
		if (chdir(arg[1]) == -1)
		{
			ft_putstr_fd("No such file or directory: ", 2);
			ft_putendl_fd(arg[1], 2);
		}
		// lstat --> No such file or directory / Is not a directory
	}
	//chdir_me avec message d'erreur
}