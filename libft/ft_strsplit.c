/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:08:37 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 13:04:39 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**map;
	size_t	i;
	size_t	nb_words;

	if (s == NULL)
		return (NULL);
	i = 0;
	nb_words = 0;
	map = NULL;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if ((map = ft_realloc_str_tab(map, NULL)) == NULL)
			return (NULL);
		map[nb_words] = ft_strcdup(s + i, c);
		i += ft_strclen(s + i, c);
		while (s[i] && s[i] == c)
			i++;
		nb_words++;
	}
	return (map);
}
