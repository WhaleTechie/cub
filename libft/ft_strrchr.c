/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:18:32 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** function is identical to strchr(), except it locates
** the last occurrence of c.
*/

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t	n;
	char	*str;

	str = (char *)s;
	n = ft_strlen(str);
	while (0 != n && str[n] != (char)c)
		n--;
	if (str[n] == (char)c)
		return ((char *)&s[n]);
	return (NULL);
}
