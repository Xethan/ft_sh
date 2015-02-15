/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 13:22:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/15 16:44:22 by ncolliau         ###   ########.fr       */
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
				//close(plist->right_fd[j]);
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
		{
			wait(NULL);
			//close(plist->right_fd[i]);
		}
		if (pid == 0)
		{
			read_stdin(line);
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
		read_stdin(line);
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
	}
}

void	left_pipe_to_fd(t_arg *plist, int old_pdes[2])
{
	pid_t	pid;
	size_t	i;

	i = 0;
	while (plist->right_fd[i] != -1)
	{
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
			//close(plist->right_fd[i]);
			if (old_pdes != NULL)
				close(old_pdes[READ_END]);
		}
		if (pid == 0)
		{
			if (old_pdes != NULL)
			{
				close(old_pdes[WRITE_END]);
				dup2(old_pdes[READ_END], STDIN_FILENO);
			}
			dup2(plist->right_fd[i], STDOUT_FILENO);
			execve(plist->arg[0], plist->arg, g_env);
		}
		i++;
	}
}

void	left_pipe_to_pipe(t_arg *plist, int new_pdes[2], int old_pdes[2])
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
		if (old_pdes != NULL)
			close(old_pdes[READ_END]);
		if (plist->next)
			close(new_pdes[WRITE_END]);
	}
	if (pid == 0)
	{
		if (old_pdes != NULL)
		{
			close(old_pdes[WRITE_END]);
			dup2(old_pdes[READ_END], STDIN_FILENO);
		}
		if (plist->next)
		{
			close(new_pdes[READ_END]);
			dup2(new_pdes[WRITE_END], STDOUT_FILENO);
		}
		execve(plist->arg[0], plist->arg, g_env);
	}
}

int		try_again(t_arg *plist, int old_pdes[2], char **path, size_t nb_path)
{
	int		ret;
	int		new_pdes[2];
	char	*line;
	int		i;

	ret = find_path(path, nb_path, plist->arg);
	access_error(ret, plist->arg[0]);
	if (ret != 1)
		return (-1);
	if (plist->nb_stop != 0)
		line = get_stdin(plist->stop, plist->nb_stop);
	if (old_pdes != NULL || (plist->left_fd[0] == -1 && plist->nb_stop == 0))
		left_pipe_to_fd(plist, old_pdes);
	fd_to_fd(plist);
	if (plist->nb_stop != 0)
		stdin_to_fd(plist, line);
	if (plist->next)
		if (pipe(new_pdes) == -1)
		{
			ft_putendl_fd("Pipe failed", 2);
			return (-1);
		}
	if (plist->next || plist->right_fd[0] == -1)
	{
		if (old_pdes != NULL || (plist->left_fd[0] == -1 && plist->nb_stop == 0))
			left_pipe_to_pipe(plist, new_pdes, old_pdes);
		fd_to_pipe(plist, new_pdes);
		if (plist->nb_stop != 0)
			stdin_to_pipe(plist, line, new_pdes);
	}
	if (plist->nb_stop != 0)
		free(line);
	i = 0;
	while (plist->right_fd[i] != -1)
	{
		close(plist->right_fd[i]);
		i++;
	}
	if (plist->next)
		try_again(plist->next, new_pdes, path, nb_path);
	return (1);
}
