/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_fd_and_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 13:22:55 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 17:05:26 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern char	**g_env;

int		fd_to_fd(t_arg *plist)
{
	int		ret;
	size_t	i;
	size_t	j;
	int		lfd;
	int		rfd;

	i = -1;
	while (plist->left_fd && plist->left_fd[++i])
	{
		j = 0;
		while (plist->right_fd && plist->right_fd[j])
		{
			if ((rfd = open_it(plist->right_fd[j], WRITE_END)) == -1)
				return (1);
			if ((lfd = open_it(plist->left_fd[i], READ_END)) == -1)
				return (1);
			ret = exec_it(plist, NULL, init_tools(NULL, NULL, lfd, rfd));
			close(lfd);
			close(rfd);
			if (ret >= 126 && ret < 255)
				return (ret);
			j++;
		}
	}
	return (ret);
}

int		fd_to_output(t_arg *plist, int new_pdes[2])
{
	t_tools	tools;
	int		ret;
	size_t	i;
	int		fd;

	i = 0;
	while (plist->left_fd && plist->left_fd[i])
	{
		if ((fd = open_it(plist->left_fd[i], READ_END)) == -1)
			return (1);
		tools = init_tools(NULL, NULL, fd, -1);
		ret = exec_it(plist, new_pdes, tools);
		close(fd);
		if (ret >= 126 && ret < 255)
			return (ret);
		i++;
	}
	return (ret);
}

int		input_to_fd(t_arg *plist, char *input)
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
		tools = init_tools(NULL, input, -1, -1);
		ret = exec_it(plist, NULL, tools);
		close(fd);
		if (ret >= 126 && ret < 255)
			return (ret);
		i++;
	}
	return (ret);
}

int		input_to_output(t_arg *plist, char *input, int new_pdes[2])
{
	t_tools	tools;

	tools = init_tools(NULL, input, -1, -1);
	return (exec_it(plist, new_pdes, tools));
}
