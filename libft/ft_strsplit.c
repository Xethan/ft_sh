/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:08:37 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/09 13:53:52 by ncolliau         ###   ########.fr       */
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

char	**ft_strsplit(char const *s, char c)
{
	char	**map;
	size_t	i;
	int		nb_words;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if ((map = ft_restralloc(map, nb_words)) == NULL)
			return (NULL);
		map[nb_words] = ft_strcdup(s + i, c);
		i += ft_strclen(s + i, c) + 1;
		while (s[i] && s[i] == c)
			i++;
		nb_words++;
	}
	return (map);
}
