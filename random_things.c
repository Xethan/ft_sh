/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 12:20:53 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/24 12:22:26 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

int		built_in(t_arg *plist, int new_pdes[2], char **path)
{
	int		exit_value;

	if (ft_strequ(plist->arg[0], "exit"))
	{
		free_env();
		if (plist->sz_arg > 1)
			exit_value = ft_atoi(plist->arg[1]);
		else
			exit_value = 0;
		lstdel(&plist);
		exit(exit_value);
	}
	if (ft_strequ(plist->arg[0], "cd"))
		change_dir(plist->arg, plist->sz_arg);
	else if (ft_strequ(plist->arg[0], "env"))
		return (ft_env(plist, new_pdes, path));
	else if (ft_strequ(plist->arg[0], "setenv"))
		ft_setenv(plist->arg + 1);
	else if (ft_strequ(plist->arg[0], "unsetenv"))
		ft_unsetenv(plist->arg, plist->sz_arg);
	else
		return (0);
	return (1);
}

int		cmds_to_stdout(t_arg *plist, int new_pdes[2], char *input, char *pip)
{
	int		ret;

	if (pip != NULL || (plist->left_fd == NULL && plist->stop == NULL))
		ret = stdin_to_output(plist, new_pdes, pip);
	if (ret >= 128 && ret < 255)
		return (ret);
	ret = fd_to_output(plist, new_pdes);
	if (ret >= 128 && ret < 255)
		return (ret);
	if (plist->stop != NULL)
		ret = input_to_output(plist, input, new_pdes);
	return (ret);
}

int		cmds(t_arg *plist, int new_pdes[2], char *input, char *pip)
{
	int		ret;

	if (plist->next)
		if (pipe(new_pdes) == -1)
		{
			ft_putendl_fd("Pipe failed", 2);
			return (128);
		}
	if (pip != NULL || (plist->left_fd == NULL && plist->stop == NULL))
		ret = stdin_to_fd(plist, pip);
	if (ret >= 128 && ret < 255)
		return (ret);
	ret = fd_to_fd(plist);
	if (ret >= 128 && ret < 255)
		return (ret);
	if (plist->stop != NULL)
		ret = input_to_fd(plist, input);
	if (ret >= 128 && ret < 255)
		return (ret);
	if (plist->next || plist->right_fd == NULL)
		ret = cmds_to_stdout(plist, new_pdes, input, pip);
	return (ret);
}

int		check_access(char *full_path)
{
	char	*bin_path;
	int		i;
	int		ret;
	t_stat	st;
	t_stat	st2;

	i = 0;
	ret = 0;
	while (full_path[i])
		i++;
	while (full_path[i] != '/' && i != 0)
		i--;
	bin_path = ft_strndup(full_path, i);
	if (i != 0 && stat(bin_path, &st) == -1)
		ret = 127;
	else if (i != 0 && access(bin_path, R_OK) == -1)
		ret = 126;
	else if (stat(full_path, &st2) == -1)
		ret = 127;
	else if (S_ISREG(st2.st_mode) == 0 || access(full_path, X_OK) == -1)
		ret = 126;
	free(bin_path);
	return (ret);
}

int		find_path(char **path, char *cmd, char **pathed_cmd)
{
	size_t	i;
	char	*tmp;
	int		ret;

	if (cmd[0] != '.' && cmd[0] != '/')
	{
		i = 0;
		while (path && path[i])
		{
			tmp = ft_strtrijoin(path[i], "/", cmd);
			if ((ret = check_access(tmp)) == 0)
				*pathed_cmd = ft_strdup(tmp);
			free(tmp);
			if (ret == 0 || ret == 126)
				return (ret);
			i++;
		}
		return (127);
	}
	*pathed_cmd = ft_strdup(cmd);
	return (check_access(cmd));
}
