/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:18:20 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:59:45 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	if (content == NULL)
		content_size = 0;
	if ((new_list->content = malloc(content_size)) == NULL)
		return (NULL);
	if (content == NULL)
		new_list->content = NULL;
	else
		ft_memmove(new_list->content, content, content_size);
	new_list->content_size = content_size;
	new_list->next = NULL;
	return (new_list);
}
