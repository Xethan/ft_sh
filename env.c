/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:12:29 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 18:07:04 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		check_options(char **arg)
{
	int		i;
	int		j;

	i = 1;
	j = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		if (arg[i][1] == '-' && arg[i][2] == '\0')
			return (i + 1);
		while (arg[i][j])
		{
			if (arg[i][j] != 'i')
			{
				ft_putstr_fd("env: illegal option -- ", 2);
				ft_putchar_fd(arg[i][j], 2);
				ft_putendl_fd("\nusage: env [-i] [name=value ...] [cmd]", 2);
				return (-1);
			}
			j++;
		}
		i++;
		j = 1;
	}
	if (i != 1)
		free_env();
	return (i);
}

int		ft_env(t_arg *plist, char **path, size_t nb_path)
{
	int		i;
	char	**tmp_env;
	char	**add_to_env;

	add_to_env = NULL;
	tmp_env = dup_env(g_env);
	i = 1;
	if (plist->sz_arg != 1)
	{
		if ((i = check_options(plist->arg)) == -1)
			return (1);
		while (plist->arg[i] && ft_strchr(plist->arg[i], '=') != NULL)
		{
			add_to_env = ft_realloc_str_tab(add_to_env, plist->arg[i]);
			i++;
		}
		ft_setenv(add_to_env);
		ft_freetab(add_to_env);
	}
	if (plist->arg[i])
	{
		plist->arg += i;
		launch_cmds(plist, NULL, path, nb_path);
		plist->arg -= i;
		free_env();
		g_env = tmp_env;
		return (2);
	}
	else
	{
		i = 0;
		while (g_env && g_env[i] != NULL)
		{
			ft_putendl(g_env[i]);
			i++;
		}
	}
	free_env();
	g_env = tmp_env;
	return (1);
}
