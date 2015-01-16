/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 14:37:40 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/16 13:19:10 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_line(char **buf, int fd)
{
	char	buffer[BUFF_SIZE + 1];
	int		read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (ft_strstr(*buf, "\n") == NULL && read_bytes != 0)
	{
		if ((read_bytes = read(fd, buffer, BUFF_SIZE)) == -1)
			return (-1);
		buffer[read_bytes] = '\0';
		tmp = *buf;
		*buf = ft_strjoin(*buf, buffer);
		free(tmp);
		ft_memset(buffer, 0, read_bytes);
	}
	return (read_bytes);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf;
	char		*tmp;
	int			read_bytes;

	if (BUFF_SIZE > MAX_SIZE_BUFFER || BUFF_SIZE <= 0 || fd == 1)
		return (-1);
	if ((read_bytes = read_line(&buf, fd)) == -1)
		return (-1);
	*line = ft_strcdup(buf, '\n');
	tmp = buf;
	buf = ft_strdup(buf + ft_strclen(buf, '\n') + 1);
	free(tmp);
	return (read_bytes == 0) ? 0 : 1;
}
