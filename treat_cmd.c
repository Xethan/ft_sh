/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 15:01:51 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/28 19:04:54 by ncolliau         ###   ########.fr       */
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
	if (ft_strnequ(s, ">", 1) == 1)
		return (1);
	if (ft_strnequ(s, ">>", 2) == 1)
		return (1);
	if (ft_strnequ(s, "<", 1) == 1)
		return (1);
	if (ft_strnequ(s, "<<", 2) == 1)
		return (1);
	return (0);
}

t_arg	**cmd_to_list(char *cmd)
{
	int		i;
	int		j;
	int		ret;
	char	*tmp;
	char	**arg;
	size_t	sz_arg;
	char	*redir;
	t_arg	**begin_list;
	t_arg	*plist;

	i = 0;
	j = 0;
	begin_list = NULL;
	while (cmd[i])
	{
		redir = NULL;
		if ((ret = is_redir(cmd + j)) != 0)
		{
			redir = ft_strsub(cmd, j, ret);
			j += ret + 1;
			i += ret + 1;
		}
		while (cmd[j] && (ret = is_redir(cmd + j)) == 0)
			j++;
		tmp = ft_strsub(cmd, i, j);
		arg = ft_sizesplit(tmp, ' ', &sz_arg);
		if (begin_list == NULL)
		{
			begin_list = (t_arg **)malloc(sizeof(t_arg*));
			*begin_list = lstnew(arg, sz_arg, redir);
			plist = *begin_list;
		}
		else
		{
			lst_creat_after(plist, arg, sz_arg, redir);
			plist = plist->next;
		}
		i = j;
	}
	return (begin_list);
}

void	treat_cmd(char **arg, size_t sz_arg)
{
	size_t	i;
	char	**cmd;
	size_t	sz_cmd;
	t_arg	**begin_list;
	t_arg	*plist;

	i = 0;
	while (i != sz_arg)
	{
		arg[i] = replace_tabs(arg[i]);
		begin_list = cmd_to_list(arg[i]);
		plist = *begin_list;
		while (plist != NULL)
		{
			ft_putendl(plist->arg[0]);
			ft_putnbr_nl(plist->sz_arg);
			ft_putendl(plist->redir);
			plist = plist->next;
		}
		cmd = ft_sizesplit(arg[i], ' ', &sz_cmd);
		cmd = tilde_and_dollar(cmd, sz_cmd);
		if (sz_cmd != 0)
		{
			if (built_in(cmd, sz_cmd) == 0)
				try_all_path(cmd);
			ft_freetab(cmd, sz_cmd);
		}
		free(arg[i]);
		i++;
		if (i == sz_arg)
			free(arg);
	}
}
