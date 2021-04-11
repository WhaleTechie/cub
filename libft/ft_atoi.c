/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:49:13 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 15:51:30 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int i;
	int x;
	int k;

	i = 0;
	x = 0;
	k = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == 45 || str[i] == '+')
	{
		if (str[i] == 45)
			k = -1;
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		x = x * 10 + (str[i] - 48);
		i++;
	}
	return (x * k);
}
