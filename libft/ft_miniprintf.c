/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/22 19:41:41 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 15:05:17 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void	disp_arg(va_list ap, char c)
{
	if (c == 'd')
		ft_putnbr(va_arg(ap, int));
	if (c == 's')
		ft_putstr(va_arg(ap, char *));
	if (c == 'c')
		ft_putchar(va_arg(ap, int));
}

int			ft_miniprintf(const char *arg, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, arg);
	while (arg[i])
	{
		if (arg[i] == '%')
		{
			if (arg[++i])
				disp_arg(ap, arg[i]);
		}
		else
			ft_putchar(arg[i]);
		i++;
	}
	va_end(ap);
	return (i);
}
