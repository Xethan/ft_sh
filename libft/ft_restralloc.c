/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restralloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 12:05:54 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/14 15:01:06 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_restralloc(char **map, int length, size_t size)
{
	char	**tmp;
	int		i;

	i = -1;
	if (length != 0)
		tmp = map;
	map = (char **)malloc((length + size + 1) * sizeof(char*));
	if (map == NULL)
		return (NULL);
	while (++i != length)
		map[i] = tmp[i];
	map[length + size] = NULL;
	if (length != 0)
		free(tmp);
	return (map);
}
