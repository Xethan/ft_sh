/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restralloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 12:05:54 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/13 12:06:13 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_restralloc(char **map, int length)
{
	char	**tmp;
	int		i;

	i = -1;
	if (length != 0)
		tmp = map;
	map = (char **)malloc((length + 2) * sizeof(char*));
	if (map == NULL)
		return (NULL);
	while (++i != length)
		map[i] = tmp[i];
	map[length + 1] = NULL;
	if (length != 0)
		free(tmp);
	return (map);
}
