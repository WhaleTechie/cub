/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:52:03 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** function copies bytes from string src to string dst.  If the character c
** (as converted to an unsigned char) occurs in the string src, the copy
** stops and a pointer to the byte after the copy of c in the string dst is
** returned.  Otherwise, n bytes are copied, and a NULL pointer is returned.
** The source and destination strings should not overlap, as the behavior is
** undefined.
*/

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*csrc;
	unsigned char	*cdst;

	i = 0;
	csrc = (unsigned char *)src;
	cdst = (unsigned char *)dst;
	while (i < n)
	{
		if (csrc[i] == (unsigned char)c)
		{
			cdst[i] = csrc[i];
			return (cdst + i + 1);
		}
		else
		{
			cdst[i] = csrc[i];
			i++;
		}
	}
	return (NULL);
}
