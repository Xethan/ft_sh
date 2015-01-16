/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:52:35 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/16 12:52:29 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	d;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	d = (char)c;
	ptr = (char *)s;
	while (*ptr && *ptr != d)
		ptr++;
	if (*ptr == d)
		return (ptr);
	return (NULL);
}
