/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:09:15 by lkrinova          #+#    #+#             */
/*   Updated: 2021/03/23 18:00:52 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int render(t_cub *flags)
{
	clean_s(*flags);
	draw_map(*flags);
	draw_player(
			(flags->allmap.player.pos.x * MAP_SCALE),
			(flags->allmap.player.pos.y * MAP_SCALE),
			flags->ml.img, 250000000);
	cast_view(&flags->allmap.player, flags);
//	cast_ray(flags);
	mlx_put_image_to_window(flags->ml.mlx_ptr, flags->ml.win_ptr, flags->ml.img
			.im, 0,0);
	return (0);
}

void cast_view(t_player *pl, t_cub *fl)
{
	float x;
	float y;
	pl->ray_st = pl->pov - FOV / 2;
	pl->ray_end = pl->pov + FOV / 2;
	int i;

	i = 0;
	while (pl->ray_st <= pl->ray_end)
	{
		x = pl->pos.x;
		y = pl->pos.y;
		while (fl->allmap.map_ar[(int)y][(int)x] != '1')
		{
			x -= sin(pl->ray_st)/MAP_SCALE;
			y -= cos(pl->ray_st)/MAP_SCALE;
			my_mlx_pixel_put(&fl->ml.img, x * MAP_SCALE, y * MAP_SCALE, 0);
		}
		fl->rays[i].ray_pos.x = x;
		fl->rays[i].ray_pos.y = y;
		fl->rays[i].dist = sqrt(pow((pl->pos.x - fl->rays[i].ray_pos.x), 2) +
				pow((pl->pos.y - fl->rays[i].ray_pos.y), 2));
		i++;
		pl->ray_st += (float)(FOV) / fl->res.x;
	}
	draw_col(fl);
}

void draw_col(t_cub *fl)
{
	int wall_start;
	int wall_end;
	int i;

	i = 0;
	while (i <= fl->res.x)
	{
		fl->dist_plane = (fl->res.x / 2) / tan(FOV / 2);
		fl->rays[i].size = 1 / fl->rays[i].dist * fl->dist_plane;
		if (fl->rays[i].size > fl->res.y)
			fl->rays[i].size = fl->res.y;
		wall_start = (int)(fl->res.y / 2 - (fl->rays[i].size /2));
		wall_end = fl->res.y - wall_start;
		while (wall_start <= wall_end)
		{
			my_mlx_pixel_put(&fl->ml.img, i, wall_start, 0);
			wall_start++;
		}
		i++;
	}
}