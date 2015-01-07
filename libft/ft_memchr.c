/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:28:45 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:52:59 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (s == NULL)
		return (NULL);
	str = (unsigned char *)s;
	i = 0;
	c = (unsigned char)c;
	while (i != n)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}
