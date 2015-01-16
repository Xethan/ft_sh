/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/16 14:42:23 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char	**g_env;

void	disp_cmd_line(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putstr(C_MAGENTA);
	ft_putstr(env("USER"));
	ft_putstr(C_NONE);
	ft_putstr(" in ");
	ft_putstr(C_CYAN);
	if (ft_strstr(dir, env("HOME")))
	{
		ft_putstr("~");
		ft_putstr(ft_strstr(dir, env("HOME")) + ft_strlen(env("HOME")));
	}
	else
		ft_putstr(dir);
	ft_putstr(C_NONE);
	ft_putstr(" > ");
	free(dir);
}

int		built_in(char **cmd, size_t sz_arg)
{
	if (ft_strequ(cmd[0], "exit"))
	{
		free_env();
		exit(EXIT_SUCCESS);
	}
	if (ft_strequ(cmd[0], "cd"))
	{
		change_dir(cmd, sz_arg);
		return (1);
	}
	if (ft_strequ(cmd[0], "env"))
	{
		ft_env();
		return (1);
	}
	if (ft_strequ(cmd[0], "setenv"))
	{
		if (sz_arg == 3)
			ft_setenv(cmd[1], cmd[2]);
		else
			ft_putendl_fd("setenv: Not the right numbers of arguments", 2);
		return (1);
	}
	if (ft_strequ(cmd[0], "unsetenv"))
	{
		if (sz_arg >= 2)
			ft_unsetenv(cmd, sz_arg);
		else
			ft_putendl_fd("unsetenv: Not enough arguments", 2);
		return (1);
	}
	return (0);
}

int		exec_cmd(char **arg, char *path)
{
	pid_t	father;
	char	*cmd;

	cmd = ft_strjoin(path, arg[0]);
	if (access(cmd, X_OK) == -1)
	{
		free(cmd);
		return (-1);
	}
	father = fork();
	if (father == 0)
	{
		execve(cmd, arg, g_env);
		free(cmd);
		return (-1);
	}
	if (father > 0)
		wait(NULL);
	free(cmd);
	return (1);
}

int		try_all_path(char **arg)
{
	char	**path;
	size_t	nb_path;
	size_t	i;
	char	*cmd;

	if (env("PATH") == NULL)
		return (-1);
	path = ft_sizesplit(env("PATH"), ':', &nb_path);
	i = 0;
	while (i != nb_path)
	{
		cmd = ft_strjoin(path[i], "/");
		if (exec_cmd(arg, cmd) == 1)
		{
			free(cmd);
			ft_freetab(path, nb_path);
			return (1);
		}
		free(cmd);
		i++;
	}
	if (exec_cmd(arg, NULL) == 1)
	{
		ft_freetab(path, nb_path);
		return (1);
	}
	ft_freetab(path, nb_path);
	return (-1);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	char	**arg;
	size_t	sz_arg;

	(void)ac;
	(void)av;
	g_env = dup_env(env);
	while (1)
	{
		disp_cmd_line();
		if (get_next_line(0, &line) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		arg = ft_sizesplit(line, ' ', &sz_arg);
		free(line);
		if (sz_arg != 0)
		{
			if (built_in(arg, sz_arg) == 0)
				if (try_all_path(arg) == -1)
				{
					ft_putstr_fd("ft_sh1: Command not found: ", 2);
					ft_putendl_fd(arg[0], 2);
				}
			ft_freetab(arg, sz_arg);
		}
	}
	free_env();
	return (0);
}
