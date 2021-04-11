/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:57:46 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/08 20:23:20 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	draw_sqaure(int x, int y, t_img img, int color)
{
	int start_x;
	int start_y;

	start_x = x - MAP_SCALE/2;
	start_y = y - MAP_SCALE/2;

/*
**  ========TOP and BOTTOM SIDES=================
*/
	while (start_y <= y + MAP_SCALE/2)
	{
		pixel_put(&img, start_x, start_y, color);
		start_y++;
	}
	start_x += MAP_SCALE;
	start_y = y - MAP_SCALE/2;
	while (start_y <= y + MAP_SCALE/2)
	{
		pixel_put(&img, start_x, start_y, color);
		start_y++;
	}
/*
**  ========LEFT and RIGHT SIDES=================
*/
	start_x = x - MAP_SCALE/2;
	start_y = y - MAP_SCALE/2;
	while (start_x <= x + MAP_SCALE/2)
	{
		pixel_put(&img, start_x, start_y, color);
		start_x++;
	}
	start_y += MAP_SCALE;
	start_x = x - MAP_SCALE/2;
	while (start_x <= x + MAP_SCALE/2)
	{
		pixel_put(&img, start_x, start_y, color);
		start_x++;
	}
}

void            pixel_put(t_img *img, int x, int y, int color)
{
	char    *dst;

	dst = img->addr + (y * img->size_x) * 4 + (x * 4);
	*(unsigned int *)dst = color;
}

void draw_map(t_cub flags)
{
	int j = 0;
	while (flags.allmap.map_ar[j] != 0)
	{
		int i = 0;
		while (flags.allmap.map_ar[j][i] != '\0')
		{
			if (flags.allmap.map_ar[j][i] == '1')
				draw_sqaure((i * MAP_SCALE + MAP_SCALE / 2), (j *
				MAP_SCALE + MAP_SCALE / 2),
				flags.ml.img, 65280);
			i++;
		}
		j++;
	}
}

unsigned int pixel_get(t_textur *textura, int x, int y)
{
	char    *dst;

	dst = textura->addr + (y * textura->width)*4 + (x * 4);
	return(*(unsigned int *)dst);
}

void draw_texture(t_cub *fl)
{

	int i;
	int j;
	unsigned int color;

	i = 0;
	while (i <= fl->allmap.no.height)
	{
		j = 0;
		while (j <= fl->allmap.no.width)
		{
			color = pixel_get(&fl->allmap.no, i, j);
			pixel_put(&fl->ml.img, i, j, color);
			j++;
		}
		i++;
	}
}

void 	draw_player(int x, int y, t_img img, int color)
{
	int start_x;
	int start_y;

	start_x = x - 2;
	start_y = y - 2;

/*
**  ========LEFT and RIGHT SIDES=================
*/
	while (start_y <= y + 2)
	{
		pixel_put(&img, start_x, start_y,  color);
		start_y++;
	}
	start_x += 4;
	start_y = y - 2;
	while (start_y <= y + 2)
	{
		pixel_put(&img,  start_x, start_y, color);
		start_y++;
	}
/*
**  ========TOP and BOTTOM SIDES=================
*/
	start_x = x - 2;
	start_y = y - 2;
	while (start_x <= x + 2)
	{
		pixel_put(&img, start_x, start_y,  color);
		start_x++;
	}
	start_y += 4;
	start_x = x - 2;
	while (start_x <= x + 2)
	{
		pixel_put(&img, start_x, start_y, color);
		start_x++;
	}
}

/*
**  ========Clean screen=================
*/

void clean_s(t_cub flags)
{
	int i;
	int j;

	j = 0;
	while (j <= (flags.res.y/2))
	{
		i = 0;
		while (i <= flags.res.x)
		{
			pixel_put(&flags.ml.img, i, j, flags.ceil_col);
			i++;
		}
		j++;
	}
	while (j <= flags.res.y)
	{
		i = 0;
		while (i <= flags.res.x)
		{
			pixel_put(&flags.ml.img, i, j, flags.floor_rgb);
			i++;
		}
		j++;
	}
}

int	move(int keycode, t_cub *fl)
{
	if (keycode == WKEY)
	{
		fl->allmap.player.pos.x += cos(fl->allmap.player.pov)/MAP_SCALE;
		fl->allmap.player.pos.y += sin(fl->allmap.player.pov)/MAP_SCALE;
	}
	else if (keycode == SKEY)
	{
		fl->allmap.player.pos.x -= cos(fl->allmap.player.pov)/MAP_SCALE;
		fl->allmap.player.pos.y -= sin(fl->allmap.player.pov)/MAP_SCALE;
	}
	else if (keycode == AKEY)
	{
		fl->allmap.player.pos.x += sin(fl->allmap.player.pov)/MAP_SCALE;
		fl->allmap.player.pos.y -= cos(fl->allmap.player.pov)/MAP_SCALE;
	}
	else if (keycode == DKEY)
	{
		fl->allmap.player.pos.x -= sin(fl->allmap.player.pov)/MAP_SCALE;
		fl->allmap.player.pos.y += cos(fl->allmap.player.pov)/MAP_SCALE;
	}
	else if (keycode == LARROW)
		fl->allmap.player.pov -= 0.2;
	else if (keycode == RARROW)
		fl->allmap.player.pov += 0.2;
	else if (keycode == ESCAP)
		exit(0);
	if (fl->allmap.player.pos.x >fl->allmap.size.x || fl->allmap.player.pos.y
	> fl->allmap.size.y)
		return(0);
	return(0);
}
