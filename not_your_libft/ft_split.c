/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchiki <bchiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:40:46 by bchiki            #+#    #+#             */
/*   Updated: 2024/11/12 16:46:46 by bchiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	inside_word;
	int	num_words;
	int	x;

	inside_word = 0;
	num_words = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] != c)
		{
			inside_word += 1;
			if (inside_word == 1)
				num_words += 1;
		}
		else
			inside_word = 0;
		x++;
	}
	return (num_words);
}

static char	**fill(char **ptr, char const *s, char c)
{
	int	len;
	int	index;
	int	first_occ;

	len = 0;
	index = 0;
	while (s[len])
	{
		if (s[len] == c)
		{
			len++;
			continue ;
		}
		first_occ = len;
		while (s[len] != c && s[len])
			len++;
		ptr[index] = malloc(sizeof(char) * (len - first_occ + 1));
		if (!ptr[index])
			return (NULL);
		ft_strlcpy(ptr[index], (s + first_occ), (len - first_occ + 1));
		index++;
	}
	ptr[index] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		num_words;
	int		i;
	char	**ptr;

	i = 0;
	if (!s)
		return (NULL);
	num_words = count(s, c);
	ptr = malloc(sizeof(char *) * (num_words + 1));
	if (!ptr)
		return (NULL);
	if (!fill(ptr, s, c))
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
