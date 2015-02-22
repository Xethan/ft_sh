/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 13:15:47 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 17:19:31 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		check_error_pipe(char *line)
{
	char	**arg;
	int		i;
	int		j;
	int		verif;

	i = 0;
	if (line[0] == '|' || ft_strlen(ft_strrchr(line, '|')) == 1)
		return (0);
	arg = ft_strsplit(line, '|');
	if (arg == NULL && ft_strchr(line, '|') != NULL)
		return (0);
	while (arg && arg[i])
	{
		j = 0;
		verif = 0;
		while (arg[i][j] && arg[i][j] != ';')
		{
			if (arg[i][j] != ' ')
				verif = 1;
			j++;
		}
		if (verif == 0)
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
	if (error == -2)
		ft_putstr_fd("ft_sh: permission denied: ", 2);
	if (error == 0)
		ft_putstr_fd("ft_sh: command not found: ", 2);
	if (error == -1)
		ft_putstr_fd("ft_sh: no such file or directory: ", 2);
	if (error != 1)
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
	ret = 1;
	while (full_path[i])
		i++;
	while (full_path[i] != '/' && i != 0)
		i--;
	bin_path = ft_strndup(full_path, i);
	if (i != 0 && stat(bin_path, &st) == -1)
		ret = -1;
	else if (i != 0 && access(bin_path, R_OK) == -1)
		ret = -2;
	else if (stat(full_path, &st2) == -1)
		ret = -1;
	else if (S_ISREG(st2.st_mode) == 0 || access(full_path, X_OK) == -1)
		ret = -2;
	free(bin_path);
	return (ret);
}

int		find_path(char **path, char **arg)
{
	size_t	i;
	char	*cmd;
	int		ret;

	if (arg[0][0] != '.' && arg[0][0] != '/')
	{
		i = 0;
		while (path && path[i])
		{
			cmd = ft_strtrijoin(path[i], "/", arg[0]);
			if ((ret = check_access(cmd)) == 1)
			{
				free(arg[0]);
				arg[0] = ft_strdup(cmd);
			}
			free(cmd);
			if (ret == 1 || ret == -2)
				return (ret);
			i++;
		}
		return (0);
	}
	else
		return (check_access(arg[0]));
}
