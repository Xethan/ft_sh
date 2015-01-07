/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 11:55:11 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/31 12:41:22 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		test;
	char	*str;

	test = 0;
	i = ft_nbrlen(n);
	if ((str = (char *)malloc((i + 1) * sizeof(char))) == NULL)
		return (NULL);
	str[i] = '\0';
	if (n == -2147483648)
		return ((str = "-2147483648"));
	if (n < 0)
	{
		test = 1;
		str[0] = '-';
		n *= -1;
	}
	while (i-- > test)
	{
		str[i] = '0' + n % 10;
		n = n / 10;
	}
	return (str);
}
