/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:33:00 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns an array of strings obtained by
** splitting ’s’ using the character ’c’ as a delimiter. The array must be
** ended by a NULL pointer.
** #1. The string to be split.
** #2. The delimiter character.
** Return value: The array of new strings resulting from the split.
** NULL if the allocation fails.
*/

#include "libft.h"

static int	w_count(char *str, char c)
{
	int		wc;
	int		i;

	i = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			while ((str[i] != c) && (str[i] != '\0'))
				i++;
			wc++;
		}
	}
	return (wc);
}

static int	w_l(char *s, char c)
{
	int		wlen;
	int		i;

	wlen = 0;
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		wlen++;
		i++;
	}
	return (wlen);
}

static char	*w_malloc(char *s, char c)
{
	char	*word;
	int		i;
	int		wlen;

	i = 0;
	wlen = w_l(s, c);
	if (!(word = (char *)malloc(sizeof(char) * (wlen + 1))))
		return (NULL);
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**w_fill(char **arr, size_t i, char *str, char c)
{
	arr[i] = w_malloc(str, c);
	if (arr[i] == NULL)
	{
		while (i--)
			free((char *)arr[i]);
		free((char **)arr);
		return (NULL);
	}
	return (arr);
}

char		**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	char	*str;
	int		w_c;

	str = (char *)s;
	if (!str)
		return (NULL);
	w_c = w_count(str, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (w_c + 1))))
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else if (i < w_c)
		{
			w_fill(arr, i, str, c);
			i++;
			str += w_l(str, c);
		}
	}
	arr[i] = 0;
	return (arr);
}
