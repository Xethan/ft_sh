/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:32:34 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/16 13:38:27 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

extern char	**g_env;

void	ft_env(void)
{
	size_t	i;

	i = 0;
	while (g_env[i] != NULL)
	{
		ft_putendl(g_env[i]);
		i++;
	}
}

void	ft_setenv(char *name, char *value)
{
	int		i;
	char	*tmp;

	if ((i = nb_env(name)) != -1)
	{
		tmp = g_env[i];
		g_env[i] = ft_strjoin(name, "=");
		free(tmp);
		tmp = g_env[i];
		g_env[i] = ft_strjoin(g_env[i], value);
		free(tmp);
		return ;
	}
	i = len_env();
	g_env = ft_restralloc(g_env, i, 1);
	g_env[i] = ft_strjoin(name, "=");
	tmp = g_env[i];
	g_env[i] = ft_strjoin(g_env[i], value);
	free(tmp);
}

void	ft_unsetenv(char **to_del, size_t sz_arg)
{
	int		i;
	int		y;
	size_t	j;
	char	**tmp;

	j = 0;
	while (j != sz_arg)
	{
		if ((i = nb_env(to_del[j])) != -1)
		{
			y = len_env();
			tmp = g_env;
			g_env = (char **)malloc(y * sizeof(char *));
			g_env[y - 1] = NULL;
			y = 0;
			while (y != i)
			{
				g_env[y] = tmp[y];
				y++;
			}
			while (tmp[y] != NULL)
			{
				g_env[y] = tmp[y + 1];
				y++;
			}
			free(tmp[i]);
			free(tmp);
		}
		j++;
	}
}
