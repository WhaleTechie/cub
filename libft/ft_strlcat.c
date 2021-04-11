/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:04:35 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** strlcat() take the full size of the destination buffer and
** guarantee NUL-termination if there is room.
** Note that room for the NUL should be included in dstsize.
** strlcat() appends string src to the end of dst.  It will append at most
** dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
** dstsize is 0 or the original dst string was longer than dstsize (in
** practice this should not happen as it means that either dstsize is
** incorrect or that dst is not a proper string).
** If the src and dst strings overlap, the behavior is undefined.
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t d_len;
	size_t s_len;

	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if ((d_len + 1) < dstsize)
	{
		while ((src[i] != '\0') && (i + d_len + 1 < dstsize))
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
	}
	if (dstsize < d_len + 1)
		return (dstsize + s_len);
	return (d_len + s_len);
}
