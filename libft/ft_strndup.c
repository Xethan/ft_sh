/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 16:51:52 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/08 18:19:29 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t length)
{
	char	*cpy;
	size_t	i;

	i = 0;
	if (length > ft_strlen(s))
		length = ft_strlen(s);
	cpy = (char *)malloc((length + 1) * sizeof(char));
	while (i != length)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
