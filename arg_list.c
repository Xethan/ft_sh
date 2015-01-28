/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 11:09:53 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/28 18:45:59 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	lstadd(t_arg **begin_list, t_arg *new)
{
	new->next = *begin_list;
	*begin_list = new;
}

t_arg	*lstnew(char **arg, size_t sz_arg, char *redir)
{
	t_arg		*new_list;

	new_list = (t_arg *)malloc(sizeof(t_arg));
	if (new_list == NULL)
		return (NULL);
	new_list->arg = arg;
	new_list->sz_arg = sz_arg;
	new_list->redir = redir;
	new_list->next = NULL;
	return (new_list);
}

void	lst_creat_after(t_arg *list, char **arg, size_t sz_arg, char *redir)
{
	t_arg		*new;

	new = lstnew(arg, sz_arg, redir);
	new->next = list->next;
	list->next = new;
}

void	lstdel(t_arg **begin_list)
{
	t_arg		*p_list;
	t_arg		*cpy;

	p_list = *begin_list;
	while (p_list)
	{
		ft_freetab(p_list->arg, p_list->sz_arg);
		free(p_list->redir);
		cpy = p_list;
		p_list = p_list->next;
		free(cpy);
	}
}

void	lst_creat_begin(t_arg **begin_list, char **arg, size_t sz_arg, char *redir)
{
	t_arg		*new;

	new = lstnew(arg, sz_arg, redir);
	lstadd(begin_list, new);
}
