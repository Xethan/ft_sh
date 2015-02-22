/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 18:50:13 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 19:37:09 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

typedef struct		s_tools
{
	char			*pipe;
	char			*input;
	int				fd_in;
	int				fd_out;
	enum e_put		in;
	enum e_put		out;
}					t_tools;

enum	e_put
{
	PIPE, FD, INPUT
};

void	child_things(t_arg *plist, int new_pdes[2], t_tools tools)
{
	if (tools.in == PIPE && tools.pipe != NULL)
		put_in_stdin(tools.pipe);
	if (tools.in == INPUT && tools.input != NULL)
		put_in_stdin(tools.input);
	if (tools.in == FD)
		dup2(tools.fd_in, STDIN_FILENO); // verifier retour
	if (tools.out == FD)
		dup2(tools.fd_out, STDOUT_FILENO); // verifier retour
	if (tools.out == PIPE && plist->next)
	{
		close(new_pdes[READ_END]); // verifier retour
		dup2(new_pdes[WRITE_END], STDOUT_FILENO); // verifier retour
	}
}

int		exec_it(t_arg *plist, int new_pdes[2], t_tools tools)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = -1; // not sure about this
	pid = fork();
	if (pid == -1)
		ft_putendl_fd("ft_sh: fork failed", 2);
	if (pid > 0)
	{
		wait(&status);
		if (tools.out == PIPE && plist->next)
			close(new_pdes[WRITE_END]); // verifier retour
		ret = get_exit_status(status);
	}
	if (pid == 0)
	{
		child_things(plist, new_pdes, tools);
		execve(plist->arg[0], plist, g_env);
		ft_putstr_fd("ft_sh: exec format error: ", 2);
		ft_putendl_fd(plist->arg[0], 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
