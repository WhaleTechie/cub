/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:09:15 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/11 06:34:51 by lkrinova         ###   ########.fr       */
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
//	draw_texture(flags);
	mlx_put_image_to_window(flags->ml.mlx_ptr, flags->ml.win_ptr, flags->ml.img
			.im, 0,0);
	return (0);
}

void draw_col(t_cub *fl, int text, int col_num)
{
	float wall_start;
	(void)text;
	float param;
	int print;
	int y;
	int i;
	unsigned int color;
	float t_st = 0;

	if (fl->rays[col_num].hitx == 0)
		t_st = fabsf(fl->rays[col_num].ray_pos.y - (int)(fl->rays[col_num]
				.ray_pos.y)) * fl->allmap.no.height;
	t_st = fabsf(fl->rays[col_num].ray_pos.x - (int)(fl->rays[col_num].ray_pos
			.x)) * fl->allmap.no.width;
//
	wall_start = roundf(fl->res.y / 2 - (fl->rays[col_num].size /2));
	param = (fl->rays[col_num].size/ fl->allmap.no.height);
	i = 0;
	while (i < fl->rays[col_num].size)
	{
		color = (pixel_get(&fl->allmap.no, i/param, t_st));
		y = 0;
		while (y <= param)
		{
			print = (wall_start + i + y);
			pixel_put(&fl->ml.img,  col_num, print, color);
			y++;
		}
		i += param;
	}
}

//void hit_text(t_rays *ray)
//{
//	if (ray->hitx > 0 && ray->hity > 0)
//		ray->hit_text
//}


void cast_view(t_player *pl, t_cub *fl)
{
	float x;
	float y;
	int i;
	int text = 0;
	//		distance to projection plane
	fl->dist_plane = fl->res.x / 2 / tan(FOV / 2);
	pl->ray_st = pl->pov - (FOV/2);
	pl->ray_end = pl->pov + (FOV /2);


	i = 0;
	while (pl->ray_st < pl->ray_end)
	{
		x = pl->pos.x;
		y = pl->pos.y;
		while (fl->allmap.map_ar[(int)y][(int)x] != '1')
		{
			x += cos(pl->ray_st)/120;
			y += sin(pl->ray_st)/120;
			pixel_put(&fl->ml.img, x * MAP_SCALE, y * MAP_SCALE, 0);
		}

//		Hits which side
		fl->rays[i].ray_pos.x = x;
		fl->rays[i].ray_pos.y = y;
		if (fl->rays[i].ray_pos.x - fabsf(fl->rays[i].ray_pos.x) > 0)
			fl->rays[i].hitx = 1;
		else
			fl->rays[i].hity = 1;

//		Distance and ray size
		fl->rays[i].dist = hypotf((fl->rays[i].ray_pos.x - pl->pos.x),
							(fl->rays[i].ray_pos.y - pl->pos.y)) * cosf
				(pl->pov - pl->ray_st);
		fl->rays[i].size = (1 / fl->rays[i].dist  * fl->dist_plane);
		if (fl->rays[i].size > fl->res.y)
			fl->rays[i].size = fl->res.y;

//		Drawing walls
		draw_col(fl, text, i);
		i++;
		pl->ray_st += (float)(FOV) / fl->res.x;
	}
}


