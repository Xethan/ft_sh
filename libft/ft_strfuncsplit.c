/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfuncsplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolliau <ncolliau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:08:37 by ncolliau          #+#    #+#             */
/*   Updated: 2015/01/08 20:25:36 by ncolliau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		n_letter(char const *s, int index, int f(char))
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
		if ((!f(s[i]) && f(s[i])) || (!f(s[i]) && i == 0))
			n_word++;
	}
	while (!f(s[i]) && s[i])
	{
		n_letter++;
		i++;
	}
	return (n_letter);
}

char	**mallocation(char const *s, int f(char))
{
	char	**tab;
	int		i;
	int		n_word;

	i = 0;
	n_word = 0;
	while (s[i])
	{
		if ((!f(s[i]) && f(s[i])) || (!f(s[i]) && i == 0))
			n_word++;
		i++;
	}
	tab = malloc((n_word + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[n_word] = NULL;
	while (n_word-- > 0)
	{
		tab[n_word] = malloc((n_letter(s, n_word + 1, f) + 1) * sizeof(char));
		if (tab[n_word] == NULL)
			return (NULL);
		tab[n_word][n_letter(s, n_word, f)] = '\0';
	}
	return (tab);
}

char	**remplissage(char const *s, char **tab, int f(char))
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	while (s[i])
	{
		while (f(s[i]) && s[i])
			i++;
		while (!f(s[i]) && s[i])
		{
			tab[y][x] = s[i];
			i++;
			x++;
		}
		while (f(s[i]) && s[i])
			i++;
		x = 0;
		y++;
	}
	return (tab);
}

char	**ft_strfuncsplit(char const *s, int f(char))
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = mallocation(s, f);
	tab = remplissage(s, tab, f);
	return (tab);
}
