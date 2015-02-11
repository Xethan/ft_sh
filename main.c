/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/11 16:59:26 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**g_env;

void	disp_cmd_line(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putstr(C_MAGENTA);
	ft_putstr(find_env("USER"));
	ft_putstr(C_NONE);
	ft_putstr(" in ");
	ft_putstr(C_CYAN);
	if (ft_strstr(dir, find_env("HOME")))
	{
		ft_putstr("~");
		ft_putstr(ft_strstr(dir, find_env("HOME")) + ft_strlen(find_env("HOME")));
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
		ft_freetab(cmd, sz_arg);
		exit(EXIT_SUCCESS);
	}
	if (ft_strequ(cmd[0], "cd"))
		change_dir(cmd, sz_arg);
	else if (ft_strequ(cmd[0], "env"))
		ft_env();
	else if (ft_strequ(cmd[0], "setenv"))
	{
		if (sz_arg == 3)
			ft_setenv(cmd[1], cmd[2]);
		else
			ft_putendl_fd("setenv: Not the right numbers of arguments", 2);
	}
	else if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd, sz_arg);
	else
		return (0);
	return (1);
}

void	quit(int signal)
{
	if (signal == SIGINT)
		ft_putchar('\n');
}

void	shell(void)
{
	char	*line;
	char	**arg;
	size_t	sz_arg;

	signal(SIGINT, quit);
	while (1)
	{
		disp_cmd_line();
		if (get_next_line(0, &line) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		// gestion d'erreur <<< >>> + ?
		arg = ft_sizesplit(line, ';', &sz_arg);
		free(line);
		do_commands(arg, sz_arg);
		if (sz_arg != 0)
			ft_freetab(arg, sz_arg);
	}
}

int		main(int ac, char **av, char **env)
{
	dup_env(env, ac, av);
	shell();
	free_env();
	return (0);
}
