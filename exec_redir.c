/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 13:22:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/16 17:20:03 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_sh.h"

extern char	**g_env;

void	fd_to_fd(t_arg *plist)
{
	pid_t	pid;
	size_t	i;
	size_t	j;

	i = 0;
	while (plist->left_fd[i] != -1)
	{
		j = 0;
		while (plist->right_fd[j] != -1)
		{
			pid = fork();
			if (pid > 0)
			{
				wait(NULL); 
				close(plist->left_fd[i]);
			}
			if (pid == 0)
			{
				dup2(plist->left_fd[i], STDIN_FILENO);
				dup2(plist->right_fd[j], STDOUT_FILENO);
				execve(plist->arg[0], plist->arg, g_env);
			}
			j++;
		}
		i++;
	}
}

void	fd_to_pipe(t_arg *plist, int new_pdes[2])
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (plist->left_fd[i] != -1)
	{
		pid = fork();
		if (pid > 0)
		{
			wait(NULL); 
			close(plist->left_fd[i]);
			if (plist->next)
				close(new_pdes[WRITE_END]);
		}
		if (pid == 0)
		{
			dup2(plist->left_fd[i], STDIN_FILENO);
			if (plist->next)
			{
				close(new_pdes[READ_END]);
				dup2(new_pdes[WRITE_END], STDOUT_FILENO);
			}
			execve(plist->arg[0], plist->arg, g_env);
		}
		i++;
	}
}

void	stdin_to_fd(t_arg *plist, char *line)
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (plist->right_fd[i] != -1)
	{
		pid = fork();
		if (pid > 0)
			wait(NULL);
		if (pid == 0)
		{
			put_in_stdin(line);
			dup2(plist->right_fd[i], STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
		}
		i++;
	}
}

void	stdin_to_pipe(t_arg *plist, char *line, int new_pdes[2])
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		if (plist->next)
			close(new_pdes[WRITE_END]);
	}
	if (pid == 0)
	{
		put_in_stdin(line);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
	}
}

void	left_pipe_to_fd(t_arg *plist, char *pipe)
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (plist->right_fd[i] != -1)
	{
		pid = fork();
		if (pid > 0)
			wait(NULL);
		if (pid == 0)
		{
			if (pipe != NULL)
				put_in_stdin(pipe);
			dup2(plist->right_fd[i], STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
		}
		i++;
	}
}

void	left_pipe_to_pipe(t_arg *plist, int new_pdes[2], char *pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Fork failed", 2);
		return ;
	}
	if (pid > 0)
	{
		wait(NULL);
		if (plist->next)
			close(new_pdes[WRITE_END]);
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
	}
}
