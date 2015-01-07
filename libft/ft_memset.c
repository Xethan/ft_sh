/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:07:59 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:53:39 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = b;
	while (i != len)
	{
		*((unsigned char *)ptr + i) = (unsigned char)c;
		i++;
	}
	return (ptr);
}
