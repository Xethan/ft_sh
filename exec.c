/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 11:17:16 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/15 16:10:43 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

char	*get_stdin(char **stop, size_t nb_stop)
{
	int		ret;
	char	*line;
	char	*stdin;
	char	*tmp;
	size_t	i;

	i = 0;
	line = NULL;
	ret = 1;
	while (i != nb_stop)
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
		i++;
	}
	return (line);
}

void	read_stdin(char *line)
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
