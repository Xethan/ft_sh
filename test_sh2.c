/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sh2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 16:35:01 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/28 14:01:11 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <fcntl.h>

int		main(void)
{
	int		pdes[2];
	//int		pdes2[2];
	//int		fd;
	char	*arg1[3];
	char 	*arg2[3];
	//char	*arg3[3];
	pid_t	father;

	arg1[0] = "/bin/ls";
	arg1[1] = "-l";
	arg1[2] = NULL;
	arg2[0] = "/bin/cat";
	arg2[1] = "-e";
	arg2[2] = NULL;
	//arg3[0] = "/usr/bin/grep";
	//arg3[1] = "libft";
	//arg3[2] = NULL;
	pipe(pdes);
	//pipe(pdes2);
	//fd = open("Test", O_RDWR | O_CREAT | O_APPEND);
	father = fork();
	if (father == 0)
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
		execve(arg1[0], arg1, NULL);
	}
	if (father > 0)
	{
		wait(NULL);
		dup2(pdes[0], STDIN_FILENO);
		//dup2(fd, STDIN_FILENO);
		close(pdes[1]);
		//dup2(pdes[1], STDOUT_FILENO);
		//close(pdes2[0]);
		execve(arg2[0], arg2, NULL);
	}
	//father = fork();
	//if (father == 0)
	//{
	//	dup2(pdes[0], STDIN_FILENO);
	//	close(pdes[1]);
	//	execve(arg3[0], arg3, NULL);
	//}
	//if (father > 0)
	//	wait(NULL);
	return (0);
}