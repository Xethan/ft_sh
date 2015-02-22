/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 17:16:54 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		open_it(char *file, int redir)
{
	int		fd;

	if (redir == WRITE_END)
	{
		if (file[0] == '>')
			fd = open(file + 1, O_CREAT | O_RDWR | O_APPEND, 0664);
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	}
	else
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("ft_sh: open failed: ", 2);
		ft_putendl_fd(file, 2);
	}
	return (fd);
}

char	*get_input(char **stop)
{
	int		ret;
	char	*input;
	char	*line;
	char	*tmp;
	size_t	i;

	i = 0;
	input = NULL;
	ret = 1;
	while (stop && stop[i])
	{
		input = NULL;
		ft_putstr("> ");
		while ((ret = get_next_line(0, &line)) == 1 && ft_strequ(line, stop[i]) == 0)
		{
			if (ret == -1)
			{
				ft_putendl_fd("Error GNL", 2);
				exit(EXIT_FAILURE);
			}
			tmp = input;
			input = ft_strtrijoin(input, line, "\n");
			free(tmp);
			free(line);
			ft_putstr("> ");
		}
		free(line);
		i++;
	}
	return (input);
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

void	put_in_stdin(char *input)
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
		ft_putstr(input);
		close(pdes[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
	close(pdes[READ_END]);
}

int		cmds_to_output(t_arg *plist, int new_pdes[2], char *input, char *pipe_out)
{
	if (pipe_out != NULL || (plist->left_fd == NULL && plist->stop == NULL))
		stdin_to_fd(plist, pipe_out);
	fd_to_fd(plist);
	if (plist->stop != NULL)
		input_to_fd(plist, input);
	if (plist->next)
		if (pipe(new_pdes) == -1)
		{
			ft_putendl_fd("Pipe failed", 2);
			return (-1);
		}
	if (plist->next || plist->right_fd == NULL)
	{
		if (pipe_out != NULL || (plist->left_fd == NULL && plist->stop == NULL))
			stdin_to_output(plist, new_pdes, pipe_out);
		fd_to_output(plist, new_pdes);
		if (plist->stop != NULL)
			input_to_output(plist, input, new_pdes);
	}
	return (1);
}
