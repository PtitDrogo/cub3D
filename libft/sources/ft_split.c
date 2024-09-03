/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfreydie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:55:27 by tfreydie          #+#    #+#             */
/*   Updated: 2023/11/23 19:35:26 by tfreydie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**sep_str(char const *s, char c, char **array, int i);
static	int	count_words(char const *s, char c);
static void	*free_all(char **array, int j);

char	**ft_split(char const *s, char c)
{
	char	**array;	
	int		str_start;

	str_start = 0;
	array = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!array)
		return (NULL);
	return (sep_str(s, c, array, str_start));
}

static	int	count_words(char const *s, char c)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	if ((s[i] != c) && s[i])
	{
		size++;
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			size++;
		i++;
	}
	return (size);
}

static void	*free_all(char **array, int j)
{
	while (j > 0)
	{
		j--;
		if (array[j])
		{
			free(array[j]);
			array[j] = NULL;
		}
	}
	free(array);
	array = NULL;
	return (NULL);
}

static	char	**sep_str(char const *s, char c, char **array, int i)
{
	int	j;
	int	k;
	int	start;

	j = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		array[j] = malloc(sizeof(char) * (i - start) + 1);
		if (!array[j])
			return (free_all(array, j));
		while (s[start] && s[start] != c)
			array[j][k++] = s[start++];
		array[j++][k] = '\0';
	}
	array[j] = NULL;
	return (array);
}
