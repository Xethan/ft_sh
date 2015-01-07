/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:08:37 by ncolliau          #+#    #+#             */
/*   Updated: 2014/12/29 17:45:05 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		n_letter(char const *s, int index, char c)
{
	int		i;
	int		n_word;
	int		n_letter;

	i = -1;
	n_word = 0;
	n_letter = 0;
	while (n_word != index)
	{
		i++;
		if ((s[i] != c && s[i - 1] == c) || (s[i] != c && i == 0))
			n_word++;
	}
	while (s[i] != c && s[i])
	{
		n_letter++;
		i++;
	}
	return (n_letter);
}

char	**mallocation(char const *s, char c)
{
	char	**tab;
	int		i;
	int		n_word;

	i = 0;
	n_word = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i - 1] == c) || (s[i] != c && i == 0))
			n_word++;
		i++;
	}
	tab = malloc((n_word + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[n_word] = NULL;
	while (n_word-- > 0)
	{
		tab[n_word] = malloc((n_letter(s, n_word + 1, c) + 1) * sizeof(char));
		if (tab[n_word] == NULL)
			return (NULL);
		tab[n_word][n_letter(s, n_word, c)] = '\0';
	}
	return (tab);
}

char	**remplissage(char const *s, char **tab, char c)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			tab[y][x] = s[i];
			i++;
			x++;
		}
		while (s[i] == c && s[i])
			i++;
		x = 0;
		y++;
	}
	return (tab);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = mallocation(s, c);
	tab = remplissage(s, tab, c);
	return (tab);
}
