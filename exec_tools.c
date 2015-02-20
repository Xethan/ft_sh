/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/20 17:16:42 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

char	*get_stdin(char **stop)
{
	int		ret;
	char	*line;
	char	*stdin;
	char	*tmp;
	size_t	i;

	i = 0;
	line = NULL;
	ret = 1;
	while (stop && stop[i])
	{
		stdin = NULL;
		ft_putstr("> ");
		while ((ret = get_next_line(0, &stdin)) == 1 && ft_strequ(stdin, stop[i]) == 0)
		{
			if (ret == -1)
			{
				ft_putendl_fd("Error GNL", 2);
				exit(EXIT_FAILURE);
			}
			tmp = line;
			line = ft_strtrijoin(line, stdin, "\n");
			free(tmp);
			free(stdin);
			ft_putstr("> ");
		}
		free(stdin);
		i++;
	}
	return (line);
}

char	*get_pipe(int old_pdes[2])
{
	char	*pipe;
	char	*tmp;
	char	buf[2];
	int		ret;

	pipe = NULL;
	close(old_pdes[WRITE_END]);
	while ((ret = read(old_pdes[READ_END], buf, 1)) != 0)
	{
		if (ret == -1)
		{
			ft_putendl_fd("Error GNL", 2);
			exit(EXIT_FAILURE);
		}
		buf[1] = '\0';
		tmp = pipe;
		pipe = ft_strjoin(pipe, buf);
		ft_memset(buf, 0, 2);
		free(tmp);
	}
	close(old_pdes[READ_END]);
	return (pipe);
}

void	put_in_stdin(char *line)
{
	pid_t	pid;
	int		pdes[2];

	pipe(pdes);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
	}
	if (pid == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		ft_putstr(line);
		close(pdes[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
	close(pdes[READ_END]);
}

int		cmds_to_output(t_arg *plist, int new_pdes[2], char *line, char *pipe_out)
{
	if (pipe_out != NULL || (plist->left_fd == NULL && plist->stop == NULL))
		input_to_fd(plist, pipe_out);
	fd_to_fd(plist);
	if (plist->stop != NULL)
		stdin_to_fd(plist, line);
	if (plist->next)
		if (pipe(new_pdes) == -1)
		{
			ft_putendl_fd("Pipe failed", 2);
			return (-1);
		}
	if (plist->next || plist->right_fd == NULL)
	{
		if (pipe_out != NULL || (plist->left_fd == NULL && plist->stop == NULL))
			input_to_output(plist, new_pdes, pipe_out);
		fd_to_output(plist, new_pdes);
		if (plist->stop != NULL)
			stdin_to_output(plist, line, new_pdes);
	}
	return (1);
}

int		launch_cmds(t_arg *plist, int old_pdes[2], char **path, size_t nb_path)
{
	int		ret;
	int		new_pdes[2];
	char	*line;
	char	*pipe_out;

	if ((ret = built_in(plist, new_pdes, path, nb_path)) != 0)
	{
		if (plist->next && ret == 1)
			launch_cmds(plist->next, new_pdes, path, nb_path);
		return (1);
	}
	line = NULL;
	pipe_out = NULL;
	ret = find_path(path, nb_path, plist->arg);
	access_error(ret, plist->arg[0]);
	if (ret != 1)
		return (-1);
	if (plist->stop != NULL)
		line = get_stdin(plist->stop);
	if (old_pdes != NULL)
	{
		pipe_out = get_pipe(old_pdes);
		close(old_pdes[READ_END]);
		close(old_pdes[WRITE_END]);
	}
	if (cmds_to_output(plist, new_pdes, line, pipe_out) == -1)
		return (-1);
	free(line);
	free(pipe_out);
	if (plist->next)
		launch_cmds(plist->next, new_pdes, path, nb_path);
	return (1);
}
