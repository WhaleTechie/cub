/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:06:23 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
** specified in ’set’ removed from the beginning and the end of the string.
** Return value: The trimmed string. NULL if the allocation fails.
** #1. The string to be trimmed.
** #2. The reference set of characters to trim.
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*s2;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen(s1 + i);
	if (len)
	{
		while (len > 0 && ft_strchr(set, s1[len + i - 1]))
			len--;
	}
	if (!(s2 = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(s2, s1 + i, len + 1);
	s2[len] = '\0';
	return (s2);
}
