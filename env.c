/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:32:34 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/14 16:34:18 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char	**ft_restralloc_no_free(char **map, int length)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = map;
	map = (char **)malloc((length + 2) * sizeof(char*));
	if (map == NULL)
		return (NULL);
	while (++i != length)
		map[i] = tmp[i];
	map[length + 1] = NULL;
	return (map);
}

char	*find_env(char *str, char **env)
{
	size_t	i;
	char	*cmp;

	i = 0;
	while (env[i] != NULL)
	{
		cmp = ft_strcdup(env[i], '=');
		if (ft_strequ(str, cmp)
		{
			free(cmp);
			return (ft_strdup(env[i] + ft_strlen(str) + 1));
		}
		free(cmp);
		i++;
	}
	return (NULL);
}

void	ft_env(t_env var)
{
	size_t	i;

	i = 0;
	while (i != var.sz)
	{
		ft_putendl(var.env[i]);
		i++;
	}
}

t_env	ft_setenv(char **arg, t_env var)
{
	size_t	i;

	i = 0;
	while (i != var.sz && !ft_strnequ(arg[1], var.env[i], ft_strlen(arg[1])))
		i++;
	if (ft_strnequ(arg[1], var.env[i], ft_strlen(arg[1])))
		var.env[i] = ft_strjoin(ft_strndup(var.env[i], ft_strclen(var.env[i], '=') + 1), arg[2]);
	else
	{
		var.env = ft_restralloc_no_free(var.env, var.sz);
		var.env[var.sz] = ft_strjoin(arg[1], "=");
		var.env[var.sz] = ft_strjoin(var.env[var.sz], arg[2]);
		var.sz++;
	}
	return (var);
}

t_env	ft_unsetenv(char *to_del, t_env var)
{
	size_t	i;
	size_t	j;
	char	**env2;

	i = 0;
	j = 0;
	while (i != var.sz && !ft_strnequ(to_del, var.env[i], ft_strlen(to_del)))
		i++;
	if (ft_strnequ(to_del, var.env[i], ft_strlen(to_del)))
	{
		env2 = (char **)malloc(var.sz * sizeof(char));
		if (env2 == NULL)
			exit(EXIT_FAILURE);
		env2[var.sz] = NULL;
		while (j != i)
		{
			env2[j] = var.env[j];
			j++;
		}
		j++;
		while (j != var.sz)
		{
			env2[j] = var.env[j];
			j++;
		}
		var.sz--;
	}
	return (var);
}
