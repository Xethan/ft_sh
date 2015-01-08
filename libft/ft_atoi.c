/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:57:01 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/05 15:54:01 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_number(const char *str, const char *cmp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] == '0')
		i++;
	while (str[i + len] >= '0' && str[i + len] <= '9')
		len++;
	if (len > ft_strlen(cmp))
		return (-1);
	else if (len == ft_strlen(cmp))
		return (ft_strcmp(cmp, str + i));
	return (1);
}

int ft_atoi(const char *str)
{
	int i;
	int num;
	int signe;

	i = 0;
	num = 0;
	signe = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		signe = 44 - str[i];
		i++;
	}
	if (check_number(str + i, "9223372036854775808") <= 0)
		return (signe == 1) ? -1 : 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + signe * (str[i] - '0');
		i++;
	}
	return (num);
}
