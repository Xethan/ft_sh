/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 16:12:29 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/24 13:04:22 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		check_options(char **arg)
{
	int		i;
	int		j;

	i = 1;
	while (arg[i] && arg[i][0] == '-')
	{
		if (arg[i][1] == '-' && arg[i][2] == '\0')
			return (i + 1);
		j = 1;
		while (arg[i][j])
		{
			free_env();
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
	}
	return (i);
}

void	put_env_in_fd(t_arg *plist)
{
	int		i;
	int		j;
	int		fd;

	j = 0;
	while (plist->right_fd && plist->right_fd[j])
	{
		if ((fd = open_it(plist->right_fd[j], WRITE_END)) == -1)
			return ;
		i = 0;
		while (g_env && g_env[i] != NULL)
		{
			ft_putendl_fd(g_env[i], fd);
			i++;
		}
		close(fd);
		j++;
	}
}

void	disp_env(t_arg *plist, int new_pdes[2])
{
	int		i;

	put_env_in_fd(plist);
	if (plist->next)
		if (pipe(new_pdes) == -1)
		{
			ft_putendl_fd("Pipe failed", 2);
			return ;
		}
	i = 0;
	while (g_env && g_env[i] != NULL)
	{
		if (plist->next)
			ft_putendl_fd(g_env[i], new_pdes[WRITE_END]);
		else if (plist->right_fd == NULL)
			ft_putendl(g_env[i]);
		i++;
	}
}

int		treat_options(t_arg *plist)
{
	char	**add_to_env;
	int		i;

	add_to_env = NULL;
	if ((i = check_options(plist->arg)) != -1)
	{
		while (plist->arg[i] && ft_strchr(plist->arg[i], '=') != NULL)
		{
			add_to_env = ft_realloc_str_tab(add_to_env, plist->arg[i]);
			i++;
		}
		if (add_to_env)
			if (ft_setenv(add_to_env) == 0)
			{
				ft_freetab(add_to_env);
				return (-1);
			}
		ft_freetab(add_to_env);
	}
	return (i);
}

int		ft_env(t_arg *plist, int new_pdes[2], char **path)
{
	int		i;
	char	**tmp_env;

	tmp_env = dup_env(g_env);
	i = treat_options(plist);
	if (i != -1 && plist->arg[i])
	{
		plist->arg += i;
		launch_cmds(plist, NULL, path);
		plist->arg -= i;
		free_env();
		g_env = tmp_env;
		return (2);
	}
	else if (i != -1)
		disp_env(plist, new_pdes);
	free_env();
	g_env = tmp_env;
	return (1);
}
