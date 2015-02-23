/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 13:15:47 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 15:59:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		split_and_check(char *cmd)
{
	char	**arg;
	int		i;
	char	*tmp;

	arg = ft_strsplit(cmd, '|');
	if (arg == NULL && ft_strchr(cmd, '|') != NULL)
		return (0);
	i = 0;
	while (arg && arg[i])
	{
		tmp = ft_strnew(ft_strlen(arg[i]) + 1);
		ft_memset(tmp, ' ', ft_strlen(tmp) + 1);
		if (ft_strequ(tmp, arg[i]))
		{
			free(tmp);
			ft_freetab(arg);
			return (0);
		}
		free(tmp);
		i++;
	}
	ft_freetab(arg);
	return (1);
}

int		check_error_pipe(char *line)
{
	char	**arg;
	int		i;

	i = 0;
	if (line[0] == '|' || ft_strlen(ft_strrchr(line, '|')) == 1)
		return (0);
	arg = ft_strsplit(line, ';');
	while (arg && arg[i])
	{
		if (split_and_check(arg[i]) == 0)
		{
			ft_freetab(arg);
			return (0);
		}
		i++;
	}
	ft_freetab(arg);
	return (1);
}

int		check_error(char *line)
{
	if (ft_strstr(line, ">>>") != NULL)
		ft_putendl_fd("ft_sh: \">>>\" is not allowed", 2);
	else if (ft_strstr(line, "<<<") != NULL)
		ft_putendl_fd("ft_sh: \"<<<\" is not allowed", 2);
	else if (ft_strstr(line, "||") != NULL)
		ft_putendl_fd("ft_sh: \"||\" is not allowed", 2);
	else if (ft_strchr(line, '|') != NULL && check_error_pipe(line) == 0)
		ft_putendl_fd("ft_sh: pipe without command", 2);
	else
		return (1);
	free(line);
	return (0);
}

void	access_error(int error, char *name)
{
	if (error == 126)
		ft_putstr_fd("ft_sh: permission denied: ", 2);
	if (error == 127)
	{
		if (name[0] != '.' && name[0] != '/')
			ft_putstr_fd("ft_sh: command not found: ", 2);
		else
			ft_putstr_fd("ft_sh: no such file or directory: ", 2);
	}
	if (error == 126 || error == 127)
		ft_putendl_fd(name, 2);
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
