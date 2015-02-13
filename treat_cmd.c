/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 15:01:51 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/13 16:44:18 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_arg	*open_files(t_arg *pnode, char *redir, char *file)
{
	int		fd;

	if (ft_strequ(redir, "<<") == 1)
	{
		pnode->stop = ft_restralloc(pnode->stop, pnode->nb_stop, 1);
		pnode->stop[pnode->nb_stop] = ft_strdup(file);
		pnode->nb_stop++;
	}
	else
	{
		if (ft_strequ(redir, "<") == 1)
		{
			fd = open(file, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("Open failed : ", 2);
				ft_putendl_fd(file, 2);
				exit(EXIT_FAILURE);
			}
			pnode->left_fd = ft_realloc_int(pnode->left_fd, fd);
		}
		else
		{
			if (ft_strequ(redir, ">") == 1)
				fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			else if (ft_strequ(redir, ">>") == 1)
				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (fd == -1)
			{
				ft_putstr_fd("Open failed : ", 2);
				ft_putendl_fd(file, 2);
				exit(EXIT_FAILURE);
			}
			pnode->right_fd = ft_realloc_int(pnode->right_fd, fd);
		}
	}
	return (pnode);
}

int		get_redir_and_file(t_arg ***pnode, char *cmd, int i, int j)
{
	char	*redir;
	char	*file;

	redir = ft_strsub(cmd, i, j);
	while (cmd[i + j] && ft_isspace(cmd[i + j]) == 1)
		j++;
	i += j;
	j = 0;
	while (cmd[i + j] && ft_isspace(cmd[i + j]) == 0)
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
	node->left_fd = (int *)malloc(1 * sizeof(int));
	node->left_fd[0] = -1;
	node->right_fd = (int *)malloc(1 * sizeof(int));
	node->right_fd[0] = -1;
	node->stop = NULL;
	node->nb_stop = 0;
	newline = get_newline(&node, cmd);
	arg = ft_sizesplit(newline, ' ', &node->sz_arg);
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
				//exec_cmd(blist, NULL, path, nb_path);
				try_again(blist, NULL, path, nb_path);
				ft_freetab(path, nb_path);
			}
			lstdel(&blist);
		}
		i++;
	}
}
