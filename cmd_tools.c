/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/08 16:16:26 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/08 16:20:00 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		is_redir(char *s)
{
	if (ft_strnequ(s, ">>", 2) == 1)
		return (2);
	if (ft_strnequ(s, ">", 1) == 1)
		return (1);
	if (ft_strnequ(s, "<<", 2) == 1)
		return (2);
	if (ft_strnequ(s, "<", 1) == 1)
		return (1);
	return (0);
}

char	*replace_tabs(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == 1)
			line[i] = ' ';
		i++;
	}
	return (line);
}

char	**tilde_and_dollar(char **cmd, size_t sz_cmd)
{
	size_t	i;
	char	*tmp;
	char	*var;

	i = 0;
	while (i != sz_cmd)
	{
		cmd[i] = replace_tabs(cmd[i]);
		if (find_env("HOME") != NULL)
			if (cmd[i][0] == '~' && (cmd[i][1] == '\0' || cmd[i][1] == '/'))
			{
				tmp = cmd[i];
				cmd[i] = ft_strjoin(find_env("HOME"), cmd[i] + 1);
				free(tmp);
			}
		if (cmd[i][0] == '$')
		{
			var = ft_strcdup(cmd[i] + 1, '/');
			if (find_env(var) != NULL)
			{
				tmp = cmd[i];
				cmd[i] = ft_strjoin(find_env(var), cmd[i] + ft_strlen(var) + 1);
				free(tmp);
			}
			free(var);
		}
		i++;
	}
	return (cmd);
}

int		*ft_realloc_int(int *tab, int length, size_t size)
{
	int		*tmp;
	int		i;

	i = -1;
	if (length != 0)
		tmp = tab;
	tab = (int *)malloc((length + size) * sizeof(int));
	if (tab == NULL)
		return (NULL);
	while (++i != length)
		tab[i] = tmp[i];
	if (length != 0)
		free(tmp);
	return (tab);
}