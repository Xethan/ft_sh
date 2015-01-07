/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:51:01 by ncolliau          #+#    #+#             */
/*   Updated: 2014/11/22 10:57:00 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_without_spaces(char const *s)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] == ',' || ft_isspace(s[i]) == 1)
		i++;
	while (s[i])
	{
		k = i;
		while (s[k] == ',' || ft_isspace(s[k]) == 1)
		{
			k++;
			if (s[k] == '\0')
				return (j);
		}
		i++;
		j++;
	}
	return (j);
}

char	*del_spaces(char const *s, char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] == ',' || ft_isspace(s[i]) == 1)
		i++;
	while (s[i])
	{
		k = i;
		while (s[k] == ',' || ft_isspace(s[k]) == 1)
			k++;
		if (s[k] == '\0')
			return (str);
		str[j] = s[i];
		i++;
		j++;
	}
	return (str);
}

char	*ft_strtrim(char const *s)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = malloc((ft_strlen_without_spaces(s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[ft_strlen_without_spaces(s)] = '\0';
	str = del_spaces(s, str);
	return (str);
}
