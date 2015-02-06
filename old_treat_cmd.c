int		is_redir(char *s)
{
	if (ft_strnequ(s, "|", 1) == 1)
		return (1);
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