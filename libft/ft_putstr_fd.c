/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:31:36 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the string ’s’ to the given file descriptor.
** #1. The string to output.
** #2. The file descriptor on which to write.
*/

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
