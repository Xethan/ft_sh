/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 16:26:08 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 18:54:29 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

void	stdin_to_fd(t_arg *plist, char *pipe)
{
	pid_t	pid;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->right_fd && plist->right_fd[i])
	{
		if ((fd = open_it(plist->right_fd[i], WRITE_END)) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			ft_putendl_fd("ft_sh: fork failed", 2);
		if (pid > 0)
			wait(NULL);
		if (pid == 0)
		{
			if (pipe != NULL)
				put_in_stdin(pipe);
			dup2(fd, STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
			ft_putstr_fd("ft_sh: exec format error: ", 2);
			ft_putendl_fd(plist->arg[0], 2);
			exit(EXIT_FAILURE);
		}
		close(fd);
		i++;
	}
}

void	stdin_to_output(t_arg *plist, int new_pdes[2], char *pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("ft_sh: fork failed", 2);
	if (pid > 0)
	{
		wait(&status);
		if (plist->next)
			close(new_pdes[WRITE_END]);
		get_exit_status(status, plist->arg[0]);
	}
	if (pid == 0)
	{
		if (pipe != NULL)
			put_in_stdin(pipe);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
		ft_putstr_fd("ft_sh: exec format error: ", 2);
		ft_putendl_fd(plist->arg[0], 2);
		exit(EXIT_FAILURE);
	}
}
