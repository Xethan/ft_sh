/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:37:35 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:55:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	size_t	ret;

	i = 0;
	j = 0;
	if (ft_strlen(dst) >= size)
		return (ft_strlen(src) + size);
	ret = ft_strlen(dst) + ft_strlen(src);
	while (dst[j])
		j++;
	while (src[i] && size - 1 - i - j != 0)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (ret);
}
