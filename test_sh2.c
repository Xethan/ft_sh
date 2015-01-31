/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sh2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 16:35:01 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/31 18:31:44 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <fcntl.h>

int		main(void)
{
	int		pdes[2];
	//int		fd;
	char	*arg1[3] = {"/bin/ls", "-l", NULL};
	char	*arg2[3] = {"/usr/bin/grep", "libft", NULL};
	pid_t	father;

	pipe(pdes);
	//fd = open("Test", O_RDWR | O_CREAT | O_APPEND);
	father = fork();
	if (father > 0)
	{
		father = fork();
		if (father > 0)
			wait(NULL);
		if (father == 0)
		{
			dup2(pdes[0], STDIN_FILENO);
			//dup2(fd, STDIN_FILENO);
			close(pdes[1]);
			//dup2(pdes[1], STDOUT_FILENO);
			execve(arg2[0], arg2, NULL);
		}
	}
	if (father == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		execve(arg1[0], arg1, NULL);
	}
	return (0);
}