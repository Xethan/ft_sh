/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 19:13:41 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/29 20:02:16 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_list;
	t_list	*old;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new = f(lst);
	begin_list = new;
	while (lst->next)
	{
		old = new;
		lst = lst->next;
		new = (t_list *)malloc(sizeof(t_list));
		if (new == NULL)
			return (NULL);
		new = f(lst);
		old->next = new;
	}
	return (begin_list);
}
