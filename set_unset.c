/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 15:32:34 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 17:09:27 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		verif_new_var(char *str)
{
	if (ft_strchr(str, '=') == NULL)
		ft_putendl_fd("usage: setenv [name=value ...]", 2);
	else if (ft_strchr(str, '=') != ft_strrchr(str, '='))
		ft_putendl_fd("setenv: only one \'=\' allowed in [name=value]", 2);
	else if (ft_strclen(str, '=') == 0)
		ft_putendl_fd("setenv: missing either name or value", 2);
	else if (ft_strlen(ft_strchr(str, '=')) == 1)
		ft_putendl_fd("setenv: missing either name or value", 2);
	else
		return (1);
	return (0);
}

int		ft_setenv(char **arg)
{
	int		i;
	int		pos;
	char	*name;

	i = 0;
	while (arg && arg[i])
	{
		if (verif_new_var(arg[i]) == 0)
			return (0);
		name = ft_strcdup(arg[i], '=');
		if ((pos = nb_env(name)) != -1)
		{
			free(g_env[pos]);
			g_env[pos] = ft_strdup(arg[i]);
		}
		else
			g_env = ft_realloc_str_tab(g_env, arg[i]);
		free(name);
		i++;
	}
	if (i == 0)
		ft_putendl_fd("usage: setenv [name=value ...]", 2);
	return (1);
}

void	ft_setenv_name_value(char *name, char *value)
{
	int		i;
	char	*tmp;

	if (ft_strchr(value, '=') != NULL || ft_strchr(name, '=') != NULL)
	{
		ft_putendl_fd("setenv: \"=\" is not allowed in env variables", 2);
		return ;
	}
	if ((i = nb_env(name)) != -1)
	{
		free(g_env[i]);
		g_env[i] = ft_strtrijoin(name, "=", value);
	}
	else
	{
		tmp = ft_strtrijoin(name, "=", value);
		g_env = ft_realloc_str_tab(g_env, tmp);
		free(tmp);
	}
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
		ft_putendl_fd("usage: unsetenv [name ...]", 2);
		return ;
	}
	while (i != sz_arg)
	{
		if ((del = nb_env(to_del[i])) != -1)
			get_env_less_one(del);
		i++;
	}
}
