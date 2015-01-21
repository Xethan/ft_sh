/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 14:39:44 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/21 12:50:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **tab, int size)
{
	int		i;

	if (tab == NULL)
		return ;
	i = 0;
	while (i != size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
