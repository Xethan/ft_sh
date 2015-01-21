/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/21 13:51:24 by ncolliau         ###   ########.fr       */
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

char	*replace_tabs(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]) == 1)
			line[i] = ' ';
		i++;
	}
	return (line);
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	char	**arg;
	size_t	sz_arg;

	dup_env(env, ac, av);
	while (1)
	{
		disp_cmd_line();
		if (get_next_line(0, &line) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		line = replace_tabs(line);
		arg = ft_sizesplit(line, ' ', &sz_arg);
		free(line);
		if (sz_arg != 0)
		{
			if (built_in(arg, sz_arg) == 0)
				try_all_path(arg);
			ft_freetab(arg, sz_arg);
		}
	}
	free_env();
	return (0);
}
