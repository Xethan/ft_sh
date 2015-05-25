/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2015/03/27 13:51:29 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

int		disp_prompt(void)
{
	char	*dir;
	char	*tmp;

	dir = NULL;
	dir = getcwd(dir, 0);
	ft_putstr(C_MAGENTA);
	if (find_env("USER"))
		ft_putstr(find_env("USER"));
	else
		ft_putstr("?");
	ft_putstr(C_NONE);
	ft_putstr(" in ");
	ft_putstr(C_CYAN);
	if (ft_strstr(dir, find_env("HOME")))
	{
		ft_putstr("~");
		tmp = ft_strstr(dir, find_env("HOME")) + ft_strlen(find_env("HOME"));
		ft_putstr(tmp);
	}
	else
		ft_putstr(dir);
	ft_putstr(C_NONE);
	ft_putstr(" > ");
	free(dir);
	return (1);
}

int		get_exit_status(int status, char *prog)
{
	int		signum;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		if (signum == SIGBUS)
			ft_miniprintf_fd(2, "ft_sh: bus error %s\n", prog);
		if (signum == SIGFPE)
			ft_miniprintf_fd(2, "ft_sh: floating point exception %s\n", prog);
		if (signum == SIGSEGV)
			ft_miniprintf_fd(2, "ft_sh: segmentation fault %s\n", prog);
		return (128 + signum);
	}
	return (0);
}

void	sighandler(int signum)
{
	(void)signum;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

void	up_shlvl(void)
{
	int		i;
	int		nbr;
	char	*lvl;

	if ((i = nb_env("SHLVL")) == -1)
		nbr = 1;
	else
		nbr = ft_atoi(g_env[i] + ft_strclen(g_env[i], '=') + 1) + 1;
	lvl = ft_itoa(nbr);
	ft_setenv_name_value("SHLVL", lvl);
	free(lvl);
}

void	lstdel(t_arg **begin_list)
{
	t_arg		*p_list;
	t_arg		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		free(p_list->cmd);
		ft_freetab(p_list->arg);
		ft_freetab(p_list->stop);
		ft_freetab(p_list->left_fd);
		ft_freetab(p_list->right_fd);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}
