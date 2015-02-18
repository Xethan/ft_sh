/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 12:05:54 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 13:04:59 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_str_tab(char **map, char *line)
{
	char	**tmp;
	int		length;
	int		i;

	i = -1;
	length = 0;
	while (map && map[length])
		length++;
	if (length != 0)
		tmp = map;
	map = (char **)malloc((length + 2) * sizeof(char*));
	if (map == NULL)
		return (NULL);
	while (++i != length)
		map[i] = tmp[i];
	map[length] = ft_strdup(line);
	map[length + 1] = NULL;
	if (length != 0)
		free(tmp);
	return (map);
}
