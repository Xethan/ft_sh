/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/18 12:54:38 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	lstdel(t_arg **begin_list)
{
	t_arg		*p_list;
	t_arg		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		ft_freetab(p_list->arg);
		ft_freetab(p_list->stop);
		ft_freetab(p_list->left_fd);
		ft_freetab(p_list->right_fd);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}
