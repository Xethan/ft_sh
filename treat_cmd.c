/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 15:01:51 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/04 16:30:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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

int		is_redir(char *s)
{
	if (ft_strnequ(s, "|", 1) == 1)
		return (1);
	if (ft_strnequ(s, ">>", 2) == 1)
		return (2);
	if (ft_strnequ(s, ">", 1) == 1)
		return (1);
	if (ft_strnequ(s, "<", 1) == 1)
		return (1);
	return (0);
}

int		get_node(char *cmd, int i, t_arg **plist)
{
	char	*redir;
	char	*tmp;
	char	**arg;
	size_t	sz_arg;
	int		j;

	j = i;
	redir = NULL;
	if ((j = is_redir(cmd + i)) != 0)
	{
		redir = ft_strsub(cmd, i, j);
		j += i;
		i = j;
	}
	while (cmd[j] && is_redir(cmd + j) == 0)
		j++;
	tmp = ft_strsub(cmd, i, j - i);
	tmp = replace_tabs(tmp);
	arg = ft_sizesplit(tmp, ' ', &sz_arg);
	arg = tilde_and_dollar(arg, sz_arg);
	free(tmp);
	if (sz_arg == 0)
		*plist = NULL;
	else
		*plist = lstnew(arg, sz_arg, redir);
	return (j);
}

t_arg	*cmd_to_list(char *cmd)
{
	int		i;
	t_arg	*blist;
	t_arg	*plist;
	t_arg	*new_node;

	i = 0;
	blist = NULL;
	while (cmd[i])
	{
		i = get_node(cmd, i, &new_node);
		if (new_node != NULL)
		{
			if (blist == NULL)
				blist = new_node;
			else
				plist->next = new_node;
			plist = new_node;
		}
	}
	return (blist);
}

void	do_commands(char **arg, size_t sz_arg)
{
	size_t	i;
	t_arg	*blist;
	char	**path;
	size_t	nb_path;

	i = 0;
	while (i != sz_arg)
	{
		blist = cmd_to_list(arg[i]);
		if (blist != NULL)
		{
			if (built_in(blist->arg, blist->sz_arg) == 0)
			{
				path = ft_sizesplit(find_env("PATH"), ':', &nb_path);
				exec_cmd(blist, NULL, path, nb_path);
				ft_freetab(path, nb_path);
			}
			lstdel(&blist);
		}
		i++;
	}
}
