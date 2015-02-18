/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 15:01:51 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 15:44:33 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_arg	*open_files(t_arg *pnode, char *redir, char *file)
{
	char	*tmp;

	if (ft_strequ(redir, "<<") == 1)
		pnode->stop = ft_realloc_str_tab(pnode->stop, file);
	else
	{
		if (ft_strequ(redir, "<") == 1)
			pnode->left_fd = ft_realloc_str_tab(pnode->left_fd, file);
		else
		{
			if (ft_strequ(redir, ">") == 1)
				pnode->right_fd = ft_realloc_str_tab(pnode->right_fd, file);
			else if (ft_strequ(redir, ">>") == 1)
			{
				tmp = ft_strjoin(">", file);
				pnode->right_fd = ft_realloc_str_tab(pnode->right_fd, tmp);
				free(tmp);
			}
		}
	}
	return (pnode);
}

int		get_redir_and_file(t_arg ***pnode, char *cmd, int i, int j)
{
	char	*redir;
	char	*file;

	redir = ft_strsub(cmd, i, j);
	while (cmd[i + j] && cmd[i + j] == ' ')
		j++;
	i += j;
	j = 0;
	while (cmd[i + j] && cmd[i + j] != ' ')
		j++;
	if (j != 0)
		file = ft_strsub(cmd, i, j);
	i += j;
	if (file && redir)
		**pnode = open_files(**pnode, redir, file);
	free(redir);
	free(file);
	return (i);
}

char	*get_newline(t_arg **pnode, char *cmd)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	newline = ft_strdup(cmd);
	while (cmd[i])
	{
		while (cmd[i] && (j = is_redir(cmd + i)) == 0)
			i++;
		if (j != 0)
		{
			j = get_redir_and_file(&pnode, cmd, i, j);
			ft_memset(newline + i, ' ', j - i);
			i = j;
		}
	}
	return (newline);
}

t_arg	*cmd_to_node(char *cmd)
{
	t_arg	*node;
	char	**arg;
	char	*newline;

	node = (t_arg *)malloc(sizeof(t_arg));
	node->left_fd = NULL;
	node->right_fd = NULL;
	node->stop = NULL;
	newline = get_newline(&node, cmd);
	arg = ft_sizesplit(newline, ' ', &node->sz_arg);
	if (node->sz_arg == 0)
		return (NULL);
	node->arg = tilde_and_dollar(arg, node->sz_arg);
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
	while (cmd && cmd[i])
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
	return (blist);
}

void	cmd_to_list_and_exec(char **arg, size_t sz_arg)
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
			path = ft_sizesplit(find_env("PATH"), ':', &nb_path);
			launch_cmds(blist, NULL, path, nb_path);
			ft_freetab(path);
			lstdel(&blist);
		}
		i++;
	}
}
