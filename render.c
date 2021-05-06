/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:09:15 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/11 09:16:18 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int render(t_cub *fl)
{
	clean_s(*fl);
	draw_map(*fl);
	draw_player(fl->m.plr.pos.x * M_SCALE, fl->m.plr.pos.y * M_SCALE,
                fl->ml.img, 250000000);
	cast_view(&fl->m.plr, fl);
	mlx_put_image_to_window(fl->ml.ml_p, fl->ml.w_p, fl->ml.img.im,
                            0, 0);
	return (0);
}

void draw_col(t_cub *fl, t_textur *tx, int c_n)
{
	double wall_start;
	double param;
	double i;
	unsigned int color;
	double t_x;
	double offset = 0;

	if (fl->rs[c_n].hitx)
	    t_x = (fl->rs[c_n].r_pos.x - (int)(fl->rs[c_n].r_pos.x)) * tx->wid;
	else
        t_x = (fl->rs[c_n].r_pos.x - (int)(fl->rs[c_n].r_pos.x)) * tx->hei;
	wall_start = (fl->res.y / 2) - (fl->rs[c_n].size / 2);
	param = (fl->rs[c_n].size / tx->hei);
	i = 0;
	if (fl->rs[c_n].size > fl->res.y)
    {
	    wall_start = 0;
	    offset = (fl->rs[c_n].size - fl->res.y) / 2 / param;
	    param = (fl->rs[c_n].size / tx->hei);
    }
	while (i <= fl->rs[c_n].size && (i < fl->res.y))
	{

	    color = pixel_get(tx, t_x, (offset + i / param));
	    pixel_put(&fl->ml.img, c_n, (int)(wall_start + i), color);
		i++;
	}
}

double is_wall(t_cub *fl, double x, double y)
{
    double size;
    double dist;
    double coef;

    size = 0;
    if (fl->m.map_ar[(int)x][(int)y] == '1')
    {
        coef = cos(fl->m.plr.pov - fl->m.plr.r_st);
        dist = (hypot((x - fl->m.plr.pos.x),(y - fl->m.plr.pos.y))) * coef;
        size = round(1 / dist * fl->dist_plane);
    }
    return (size);
}

void cast_view(t_player *pl, t_cub *fl)
{
    float x;
    float y;
    int i;

    float coef;

    //		distance to projection plane
    fl->dist_plane = fl->res.x / 2 / tan(FOV / 2);
    pl->r_st = pl->pov - (FOV/2);
    pl->r_end = pl->pov + (FOV /2);


    i = 0;
    while (pl->r_st < pl->r_end)
    {
        x = pl->pos.x;
        y = pl->pos.y;
        while (fl->m.map_ar[(int)y][(int)x] != '1')
        {
            x += cos(pl->r_st)/120;
            y += sin(pl->r_st)/120;
            pixel_put(&fl->ml.img, x * M_SCALE, y * M_SCALE, 0);
        }

//		Hits which side
        fl->rs[i].r_pos.x = x;
        fl->rs[i].r_pos.y = y;
        if (fl->rs[i].r_pos.x - fabs(fl->rs[i].r_pos.x) > 0)
            fl->rs[i].hitx = 1;
        else
            fl->rs[i].hity = 1;

//		Distance and ray size
        coef = cosf(pl->pov - pl->r_st) + 0.1;
        fl->rs[i].dist = hypotf((fl->rs[i].r_pos.x - pl->pos.x),(fl->rs[i].r_pos.y - pl->pos.y)) * cosf(pl->pov - pl->r_st);
        fl->rs[i].size = 	(1 / fl->rs[i].dist  * fl->dist_plane);

//		Drawing walls

        draw_col(fl, &fl->m.no, i); // text добавить
        i++;
        pl->r_st += (float)(FOV) / fl->res.x;
    }
}

int    f_quadrant(double angle)
{
    int quadrant;

    quadrant = 0;
    if (cos(angle) > 0 && sin(angle) > 0)
        quadrant = 1;
    else if (sin(angle) > 0 && cos(angle) < 0)
        quadrant = 2;
    else if (cos(angle) > 0 && sin(angle) < 0)
        quadrant = 4;
    else quadrant = 3;
    return (quadrant);
}
