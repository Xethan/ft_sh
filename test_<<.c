/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_<<.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 16:35:09 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/10 17:15:09 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	main(int ac, char ** av)
{
	int		ret;
	char	*line;
	char	*stdin;
	char	*tmp;
	pid_t	pid;
	int		i;
	char	*arg[3] = {"cat", "-e", NULL};
	int		pdes[2];

	i = 1;
	line = NULL;
	ret = 1;
	while (i != ac)
	{
		stdin = NULL;
		ft_putstr("> ");
		while ((ret = get_next_line(0, &stdin)) == 1 && ft_strequ(stdin, av[i]) == 0)
		{
			if (ret == -1)
			{
				ft_putendl_fd("Error GNL", 2);
				return (0);
			}
			tmp = line;
			line = ft_strtrijoin(line, stdin, "\n");
			free(tmp);
			free(stdin);
			ft_putstr("> ");
	}
	i++;
	}
	pipe(pdes);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		close(pdes[WRITE_END]);
		dup2(pdes[READ_END], STDIN_FILENO);
		execve("/bin/cat", arg, NULL);
	}
	if (pid == 0)
	{
		close(pdes[READ_END]);
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		ft_putstr(line);
		close(pdes[WRITE_END]);
	}
	close(pdes[READ_END]);
	return (0);
}