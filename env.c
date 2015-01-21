/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:32:34 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/21 12:35:15 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

extern char	**g_env;

void	up_shlvl(void)
{
	int		i;
	int		nbr;
	char	*lvl;

	if ((i = nb_env("SHLVL")) == -1)
		nbr = 1;
	else
		nbr = ft_atoi(g_env[i] + ft_strclen(g_env[i], '=') + 1) + 1;
	lvl = ft_itoa(nbr);
	ft_setenv("SHLVL", lvl);
	free(lvl);
}

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

void	get_env_less_one(int to_del)
{
	char	**tmp;
	int		len;
	int		i;

	tmp = g_env;
	len = len_env();
	g_env = (char **)malloc(len * sizeof(char *));
	g_env[len - 1] = NULL;
	i = 0;
	while (i != to_del)
	{
		g_env[i] = tmp[i];
		i++;
	}
	while (tmp[i] != NULL)
	{
		g_env[i] = tmp[i + 1];
		i++;
	}
	free(tmp[to_del]);
	free(tmp);
}

void	ft_unsetenv(char **to_del, size_t sz_arg)
{
	size_t	i;
	int		del;

	i = 0;
	if (sz_arg <= 1)
	{
		ft_putendl_fd("unsetenv: Not enough arguments", 2);
		return ;
	}
	while (i != sz_arg)
	{
		if ((del = nb_env(to_del[i])) != -1)
			get_env_less_one(del);
		i++;
	}
}
