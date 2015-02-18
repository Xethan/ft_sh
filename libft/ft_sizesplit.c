/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:08:37 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 13:08:19 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sizesplit(char const *s, char c, size_t *size)
{
	char	**map;
	size_t	i;
	size_t	nb_words;

	map = NULL;
	i = 0;
	nb_words = 0;
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i] != '\0')
	{
		if ((map = ft_realloc_str_tab(map, NULL)) == NULL)
			return (NULL);
		map[nb_words] = ft_strcdup(s + i, c);
		i += ft_strclen(s + i, c);
		while (s[i] && s[i] == c)
			i++;
		nb_words++;
	}
	*size = nb_words;
	return (map);
}
