/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 12:55:27 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 17:55:48 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**g_env;

int		built_in(t_arg *plist, int new_pdes[2], char **path)
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
		return (ft_env(plist, new_pdes, path));
	else if (ft_strequ(plist->arg[0], "setenv"))
	{
		if (plist->sz_arg != 1)
			ft_setenv(plist->arg + 1);
		else
			ft_putendl_fd("ft_sh: usage: setenv [name=value ...]", 2);
	}
	else if (ft_strequ(plist->arg[0], "unsetenv"))
		ft_unsetenv(plist->arg, plist->sz_arg);
	else
		return (0);
	return (1);
}

int		launch_cmds(t_arg *plist, int old_pdes[2], char **path)
{
	int		ret;
	int		new_pdes[2];
	char	*input;
	char	*pipe_out;

	if ((ret = built_in(plist, new_pdes, path)) != 0)
	{
		if (plist->next && ret == 1)
			launch_cmds(plist->next, new_pdes, path);
		return (1);
	}
	input = NULL;
	pipe_out = NULL;
	ret = find_path(path, plist->arg);
	access_error(ret, plist->arg[0]);
	if (ret != 1)
		return (-1);
	if (plist->stop != NULL)
		input = get_input(plist->stop);
	if (old_pdes != NULL)
	{
		pipe_out = get_pipe(old_pdes);
		close(old_pdes[READ_END]);
		close(old_pdes[WRITE_END]);
	}
	if (cmds_to_output(plist, new_pdes, input, pipe_out) == -1)
		return (-1);
	free(input);
	free(pipe_out);
	if (plist->next)
		launch_cmds(plist->next, new_pdes, path);
	return (1);
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
