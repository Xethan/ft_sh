/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:29:46 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/16 13:54:28 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	void	*cpy;

	i = 0;
	if (dst == NULL || src == NULL)
		return (NULL);
	if ((cpy = malloc(len * sizeof(*src))) == NULL)
		return (NULL);
	while (i != len)
	{
		*((char *)cpy + i) = *((char *)src + i);
		i++;
	}
	i = 0;
	while (i != len)
	{
		*((char *)dst + i) = *((char *)cpy + i);
		i++;
	}
	free(cpy);
	return (dst);
}
