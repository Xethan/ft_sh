/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:18:11 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:56:39 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	d;
	char	*ptr;
	int		i;

	if (s == NULL)
		return (NULL);
	d = c;
	i = 0;
	ptr = (char *)s;
	while (*ptr)
	{
		ptr++;
		i++;
	}
	while (i != 0 && *ptr != d)
	{
		ptr--;
		i--;
	}
	if (*ptr == d)
		return (ptr);
	return (NULL);
}
