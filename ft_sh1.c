/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/14 15:54:45 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	disp_cmd_line(t_env var)
{
	char	*dir;
	char	*tmp;

	dir = NULL;
	dir = getcwd(dir, 0);
	var.pwd = ft_strdup(dir);
	ft_putstr(C_MAGENTA);
	ft_putstr(var.user);
	ft_putstr(C_NONE);
	ft_putstr(" in ");
	ft_putstr(C_CYAN);
	if (ft_strstr(dir, var.home))
	{
		tmp = dir;
		dir = ft_strdup(ft_strstr(dir, var.home) + ft_strlen(var.home));
		free(tmp);
		ft_putstr("~");
	}
	ft_putstr(dir);
	ft_putstr(C_NONE);
	ft_putstr(" > ");
	//free(dir);
}

int		built_in(char **cmd, t_env *var, size_t sz_arg, pid_t father)
{
	if (ft_strequ(cmd[0], "exit"))
		kill(father, SIGINT); // Check return
	if (ft_strequ(cmd[0], "cd"))
	{
		change_dir(cmd, *var, sz_arg);
		return (1);
	}
	if (ft_strequ(cmd[0], "env"))
	{
		ft_env(*var);
		return (1);
	}
	if (ft_strequ(cmd[0], "setenv"))
	{
		if (cmd[1])
			*var = ft_setenv(cmd, *var);
		return (1);
	}
	if (ft_strequ(cmd[0], "unsetenv"))
	{
		if (cmd[1])
			*var = ft_unsetenv(cmd[1], *var);
		else
			ft_putendl_fd("unsetenv: Not enough arguments", 2);
		return (1);
	}
	return (0);
}

int		exec_cmd(char **arg, char *path)
{
	char	*cmd;

	path = ft_strjoin(path, "/");
	cmd = ft_strjoin(path, arg[0]);
	execve(cmd, arg, NULL);
	free(cmd);
	free(path);
	return (-1);
}

t_env	shell(pid_t father, t_env var)
{
	char	**arg;
	char	*line;
	size_t	i;
	size_t	sz_arg;

	i = 0;
	disp_cmd_line(var);
	get_next_line(0, &line);
	arg = ft_sizesplit(line, ' ', &sz_arg);
	free(line);
	if (built_in(arg, &var, sz_arg, father) == 1)
		return (var);
	while (i != var.nb_path && sz_arg != 0)
	{
		if (exec_cmd(arg, var.path[i]) == 1)
			return (var);
		i++;
	}
	execve(arg[0], arg, NULL);
	ft_putstr_fd("ft_sh1: Command not found: ", 2);
	ft_putendl_fd(arg[0], 2);
	free(arg);
	return (var);
}

int		get_nb_path(char *path)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (path[i])
	{
		if (path[i] == ':')
			nb++;
		i++;
	}
	return (nb + 1);
}

int		main(int ac, char **av, char **env)
{
	pid_t	father;
	t_env	var;

	(void)ac;
	(void)av;
	var.env = env;
	var.sz = 0;
	while (env && env[var.sz])
	{
		if (ft_strnequ(env[var.sz], "PATH", 4))
			var.path = ft_sizesplit(env[var.sz] + 5, ':', &(var.nb_path));
		if (ft_strnequ(env[var.sz], "HOME", 4))
			var.home = ft_strdup(env[var.sz] + 5);
		if (ft_strnequ(env[var.sz], "LOGNAME", 7))
			var.user = ft_strdup(env[var.sz] + 8);
		var.sz++;
	}
	var.old_pwd = ft_strdup(var.home);
	while (1)
	{
		father = fork();
		if (father > 0)
			wait(NULL);
		if (father == 0)
			var = shell(father, var);
	}
	return (0);
}
