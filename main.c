/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/16 17:42:37 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**g_env;

void	disp_prompt(void)
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

int		built_in(t_arg *plist)
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
		ft_env();
	else if (ft_strequ(plist->arg[0], "setenv"))
	{
		if (plist->sz_arg == 3)
			ft_setenv(plist->arg[1], plist->arg[2]);
		else
			ft_putendl_fd("ft_sh: usage: setenv [name] [value]", 2);
	}
	else if (ft_strequ(plist->arg[0], "unsetenv"))
		ft_unsetenv(plist->arg, plist->sz_arg);
	else
		return (0);
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
	else
		return (1);
	free(line);
	return (0);
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
		disp_prompt();
		if (get_next_line(0, &line) == -1)
		{
			ft_putendl_fd("Error get_next_line", 2);
			exit(EXIT_FAILURE);
		}
		if (check_error(line) == 1)
		{
			arg = ft_sizesplit(line, ';', &sz_arg);
			free(line);
			cmd_to_list_and_exec(arg, sz_arg);
			if (sz_arg != 0)
				ft_freetab(arg, sz_arg);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	dup_env(env, ac, av);
	shell();
	free_env();
	return (0);
}
