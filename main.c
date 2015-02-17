/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/17 18:01:52 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**g_env;

int		disp_prompt(void)
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
	return (1);
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

void	quit(int signal)
{
	if (signal == SIGBUS)
		ft_putendl_fd("ft_sh: bus error", 2);
	if (signal == SIGFPE)
		ft_putendl_fd("ft_sh: floating point exception", 2);
	if (signal == SIGSEGV)
		ft_putendl_fd("ft_sh: segmentation fault", 2);
}

void	shell(void)
{
	int		ret;
	char	*line;
	char	**arg;
	size_t	sz_arg;

	signal(SIGINT, quit);
	signal(SIGQUIT, quit);
	signal(SIGSEGV, quit);
	signal(SIGBUS, quit);
	signal(SIGFPE, quit);
	ret = -1;
	while (disp_prompt() && (ret = get_next_line(0, &line)) == 1)
	{
		line = replace_tabs(line);
		if (check_error(line) == 1)
		{
			arg = ft_sizesplit(line, ';', &sz_arg);
			free(line);
			cmd_to_list_and_exec(arg, sz_arg);
			if (sz_arg != 0)
				ft_freetab(arg);
		}
	}
	(ret == -1) ? ft_putendl_fd("Error get_next_line", 2) : ft_putchar('\n');
}

int		main(int ac, char **av, char **env)
{
	dup_env(env, ac, av);
	shell();
	free_env();
	return (0);
}
