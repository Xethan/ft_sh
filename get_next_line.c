/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 14:37:40 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/07 18:19:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_line(char **buf, int fd)
{
	char	buffer[BUFF_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	while (ft_strstr(*buf, "\n") == NULL && read_bytes != 0)
	{
		if ((read_bytes = read(fd, buffer, BUFF_SIZE)) == -1)
			return (-1);
		buffer[read_bytes] = '\0';
		if (*buf)
			*buf = ft_strjoin(*buf, buffer);
		else
			*buf = ft_strdup(buffer);
	}
	return (read_bytes);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf;
	char		**lines;
	int			read_bytes;

	if (BUFF_SIZE > MAX_SIZE_BUFFER || BUFF_SIZE <= 0 || fd == 1)
		return (-1);
	if ((read_bytes = read_line(&buf, fd)) == -1)
		return (-1);
	if (ft_strstr(buf, "\n"))
		lines = ft_strsplit(buf, '\n');
	else
	{
		lines = (char **)malloc(sizeof(char *));
		lines[0] = ft_strdup(buf);
	}
	*line = ft_strdup(lines[0]);
	buf += ft_strlen(lines[0]) + 1;
	if (read_bytes != 0)
		return (1);
	else
	{
		//free des machins (lines, buf)
		return (0);
	}
}
