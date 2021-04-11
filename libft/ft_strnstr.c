/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:06:15 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** locates the first occurrence of the null-terminated string needle in the
** string haystack, where not more than len characters are searched.
** Characters that appear after a `\0' character are not searched.
** If needle is an empty string, haystack is returned; if needle occurs
** nowhere in haystack, NULL is returned;
** otherwise a pointer to the first character of the first occurrence of
** needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t h_len;

	if (!(*needle))
		return ((char*)haystack);
	if (len == 0)
		return (NULL);
	h_len = ft_strlen(haystack);
	if (ft_strlen(needle) > len)
		return (NULL);
	j = 0;
	while (haystack[j] && j < len)
	{
		i = 0;
		while (needle[i] == haystack[j + i] && j + i < len && j + i < h_len)
			i++;
		if (needle[i] == '\0')
			return ((char *)haystack + j);
		j++;
	}
	return (NULL);
}
