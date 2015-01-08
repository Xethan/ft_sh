/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/08 14:36:33 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	disp_cmd_line(t_env var)
{
	char	*dir;
	char	*tmp;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putstr(var.user);
	ft_putstr(" in ");
	if (ft_strstr(dir, var.home))
	{
		tmp = dir;
		dir = ft_strdup(ft_strstr(dir, var.home) + ft_strlen(var.home));
		free(tmp);
		ft_putstr("~");
	}
	ft_putstr(dir);
	ft_putstr(" > ");
}

void	exec_cmd(pid_t father, t_env var)
{
	char	*cmd;
	char	**arg;
	char	*line;

	disp_cmd_line(var);
	get_next_line(0, &line);
	if (ft_strequ(line, "exit"))
		kill(father, SIGINT); // Check return
	arg = ft_strsplit(line, ' ');
	cmd = ft_strjoin("/bin/", arg[0]);
	if (execve(cmd, arg, NULL) == -1)
	{
		ft_putstr_fd("ft_sh1: Command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else
		ft_putchar('\n');
	free(line);
	free(cmd);
	free(arg);
}

int		main(int ac, char **av, char **env)
{
	pid_t	father;
	t_env	var;

	(void)ac;
	(void)av;
	while (env && *env)
	{
		if (ft_strstr(*env, "PATH"))
		{
			var.path = ft_strsplit(*env + 5, ':');
			//var.nb_path = get_nb_path(*env + 5);
		}
		if (ft_strstr(*env, "HOME"))
			var.home = *env + 5;
		if (ft_strstr(*env, "LOGNAME"))
			var.user = *env + 8;
		env++;
	}
	while (1)
	{
		father = fork();
		if (father > 0)
			wait(NULL);
		if (father == 0)
			exec_cmd(father, var);
	}
	return (0);
}
