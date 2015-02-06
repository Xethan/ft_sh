/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 15:01:51 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/06 14:55:13 by ncolliau         ###   ########.fr       */
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

char	*get_newline(t_arg **pnode, char *cmd)
{
	char	*newline;
	char	*redir;
	char	*file;
	int		fd;
	int		i;
	int		j;

	i = 0;
	newline = ft_strdup(cmd);
	while (cmd[i])
	{
		file = NULL;
		redir = NULL;
		while (cmd[i] && (j = is_redir(cmd + i)) == 0)
			i++;
		if (j != 0)
		{
			redir = ft_strsub(cmd, i, j);
			while (cmd[i + j] && ft_isspace(cmd[i + j]) == 1)
				j++;
			ft_memset(newline + i, ' ', j);
			i += j;
			j = 0;
			while (cmd[i + j] && ft_isspace(cmd[i + j]) == 0)
				j++;
			if (j != 0)
				file = ft_strsub(cmd, i, j);
			ft_memset(newline + i, ' ', j);
			i += j;
		}
		if (file != NULL && redir != NULL)
		{
			if (ft_strequ(redir, ">") == 1)
				fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			else if (ft_strequ(redir, ">>") == 1)
				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
			else if (ft_strequ(redir, "<") == 1)
				fd = open(file, O_RDONLY) * -1;
			if (fd == -1 || fd == 1)
			{
				ft_putstr_fd("Open failed : ", 2);
				ft_putendl_fd(file, 2);
				exit(EXIT_FAILURE);
			}
			else
			{
				(*pnode)->fd_tab = ft_realloc_int((*pnode)->fd_tab, (*pnode)->sz, 1);
				(*pnode)->fd_tab[(*pnode)->sz] = fd;
				(*pnode)->sz++;
			}
			free(redir);
			free(file);
		}
	}
	return (newline);
}

t_arg	*cmd_to_node(char *cmd)
{
	t_arg	*node;
	char	**arg;
	size_t	sz_arg;
	char	*newline;

	node = (t_arg *)malloc(sizeof(t_arg));
	node->fd_tab = NULL;
	node->sz = 0;
	newline = get_newline(&node, cmd);
	arg = ft_sizesplit(newline, ' ', &sz_arg);
	arg = tilde_and_dollar(arg, sz_arg);
	node->arg = arg;
	node->sz_arg = sz_arg;
	node->next = NULL;
	free(newline);
	free(cmd);
	return (node);
}

t_arg	*cmd_to_list(char *arg)
{
	t_arg	*blist;
	t_arg	*plist;
	t_arg	*new_node;
	char	**cmd;
	int		i;

	cmd = ft_strsplit(arg, '|');
	blist = NULL;
	i = 0;
	while (cmd[i] != NULL)
	{
		new_node = cmd_to_node(cmd[i]);
		if (new_node != NULL)
		{
			if (blist == NULL)
				blist = new_node;
			else
				plist->next = new_node;
			plist = new_node;
		}
		i++;
	}
	free(cmd);
	return	(blist);
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
			//lstdel(&blist);
		}
		i++;
	}
}
