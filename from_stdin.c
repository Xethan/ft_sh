/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 16:26:08 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 17:14:11 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char **g_env;

int		stdin_to_fd(t_arg *plist, char *pipe)
{
	t_tools	tools;
	int		ret;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->right_fd && plist->right_fd[i])
	{
		if ((fd = open_it(plist->right_fd[i], WRITE_END)) == -1)
			return (1);
		tools = init_tools(pipe, NULL, -1, fd);
		ret = exec_it(plist, NULL, tools);
		close(fd);
		if (ret >= 126 && ret < 255)
			return (ret);
		i++;
	}
	return (ret);
}

int		stdin_to_output(t_arg *plist, int new_pdes[2], char *pipe)
{
	t_tools	tools;

	tools = init_tools(pipe, NULL, -1, -1);
	return (exec_it(plist, new_pdes, tools));
}
