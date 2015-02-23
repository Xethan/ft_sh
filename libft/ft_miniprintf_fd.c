/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniprintf_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 14:25:42 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/23 15:05:12 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static void	disp_arg(va_list ap, char c, int fd)
{
	if (c == 'd')
		ft_putnbr_fd(va_arg(ap, int), fd);
	if (c == 's')
		ft_putstr_fd(va_arg(ap, char *), fd);
	if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), fd);
}

int			ft_miniprintf_fd(int fd, const char *arg, ...)
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
				disp_arg(ap, arg[i], fd);
		}
		else
			ft_putchar_fd(arg[i], fd);
		i++;
	}
	va_end(ap);
	return (i);
}
