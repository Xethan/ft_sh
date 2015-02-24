/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/24 12:20:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**g_env;

int		recurse(t_arg *plist, int pdes[2], char **path, int ret)
{
	if (ret >= 128 && ret < 255)
	{
		if (plist->next)
		{
			ft_putstr_fd("ft_sh: pipe chaining interrupted by an error ", 2);
			ft_miniprintf_fd(2, "while executing %s\n", plist->arg[0]);
		}
		return (ret);
	}
	if (plist->next)
		ret = launch_cmds(plist->next, pdes, path);
	return (ret);
}

int		launch_cmds(t_arg *plist, int old_pdes[2], char **path)
{
	int		ret;
	int		new_pdes[2];
	char	*input;
	char	*pip;

	if ((ret = built_in(plist, new_pdes, path)) != 0)
	{
		if (plist->next && ret == 1)
			ret = launch_cmds(plist->next, new_pdes, path);
		return (ret);
	}
	input = NULL;
	pip = NULL;
	if (plist->stop != NULL)
		input = get_input(plist->stop);
	if (old_pdes != NULL)
	{
		pip = get_pipe(old_pdes);
		close(old_pdes[READ_END]);
		close(old_pdes[WRITE_END]);
	}
	ret = cmds(plist, new_pdes, input, pip);
	free(input);
	free(pip);
	return (recurse(plist, new_pdes, path, ret));
}

void	cmd_to_list_and_exec(char **arg)
{
	size_t	i;
	t_arg	*blist;
	char	**path;

	i = 0;
	while (arg && arg[i])
	{
		blist = cmd_to_list(arg[i]);
		if (blist != NULL)
		{
			path = ft_strsplit(find_env("PATH"), ':');
			launch_cmds(blist, NULL, path);
			ft_freetab(path);
			lstdel(&blist);
		}
		i++;
	}
}

void	shell(void)
{
	int		ret;
	char	*line;
	char	**arg;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGSEGV, sighandler);
	ret = -1;
	while (disp_prompt() && (ret = get_next_line(0, &line)) == 1)
	{
		line = replace_tabs(line);
		if (check_error(line) == 1)
		{
			arg = ft_strsplit(line, ';');
			free(line);
			cmd_to_list_and_exec(arg);
			ft_freetab(arg);
		}
	}
	(ret == -1) ? ft_putendl_fd("Error get_next_line", 2) : ft_putchar('\n');
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_env = dup_env(env);
	up_shlvl();
	shell();
	free_env();
	return (0);
}
