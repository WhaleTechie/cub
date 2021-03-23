/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:06:32 by lkrinova          #+#    #+#             */
/*   Updated: 2021/03/23 16:18:08 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float get_pov(char c)
{
	int angle;

	angle = 0.0;
	if (c == 'E')
		angle = (float)(M_PI / 2);
	else if (c == 'S')
		angle = (float)M_PI;
	else if (c == 'W')
		angle = (float)(M_PI + M_PI/2);
	return(angle);
}

void rays_arr_init(t_cub *flags)
{
	if(!(flags->rays = malloc((flags->res.x) * sizeof(t_rays))))
		ft_putstr_fd("Error in mallocing ray array", 2);
}