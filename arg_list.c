/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2015/02/08 14:48:56 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_arg	*lstnew(char **arg, size_t sz_arg, int *fd_tab, int sz)
{
	t_arg		*new_node;

	new_node = (t_arg *)malloc(sizeof(t_arg));
	if (new_node == NULL)
		return (NULL);
	new_node->arg = arg;
	new_node->sz_arg = sz_arg;
	new_node->fd_tab = fd_tab;
	new_node->sz = sz;
	new_node->next = NULL;
	return (new_node);
}

void	lstdel(t_arg **begin_list)
{
	t_arg		*p_list;
	t_arg		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		ft_freetab(p_list->arg, p_list->sz_arg);
		free(p_list->fd_tab);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}

