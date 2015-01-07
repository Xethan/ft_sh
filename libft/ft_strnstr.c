/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:28:43 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:56:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int		i;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	ptr = (char *)s1;
	if (s2[0] == '\0')
		return (ptr);
	while (*ptr && n-- != 0)
	{
		if (*ptr == s2[0])
		{
			i = 0;
			while (ptr[i] == s2[i] && n + 1 - i != 0 && ptr[i] != '\0')
				i++;
			if (s2[i] == '\0')
				return (ptr);
		}
		ptr++;
	}
	return (NULL);
}
