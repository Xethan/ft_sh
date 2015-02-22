/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrijoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 16:28:56 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/22 16:29:09 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrijoin(char *s1, char *s2, char *s3)
{
	char	*tmp;

	tmp = ft_strjoin(s2, s3);
	s1 = ft_strjoin(s1, tmp);
	free(tmp);
	return (s1);
}
