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

void draw_col(t_cub *fl, t_textur tx, int c_n)
{
	double wall_start;
	double param;
	double i;
	unsigned int color;
	double t_x;
	double offset;

    offset = 0;
    param = (fl->rs[c_n].size / tx.hei);

	if (fl->rs[c_n].hitx == 1)
    {
        t_x = (fl->rs[c_n].r_pos.x - (int)(fl->rs[c_n].r_pos.x)) * tx.wid;
        wall_start = (fl->res.y / 2) - (fl->rs[c_n].size / 2);
        i = 0;
	    if (fl->rs[c_n].size > fl->res.y)
        {
	        wall_start = 0;
	        offset = (fl->rs[c_n].size - fl->res.y) / 2 / param;

        }
	    while (i < fl->rs[c_n].size && (i < fl->res.y))
	    {
//	        printf("ofset + 1/param %f\n",(offset + i / param));
            color = pixel_get(&tx, t_x, (offset + i / param));
            pixel_put(&fl->ml.img, c_n, (int)(wall_start + i), color);
            i++;
	    }
    }
	else
    {
        t_x = (fl->rs[c_n].r_pos.y - (int)(fl->rs[c_n].r_pos.y)) * tx.wid;
	    wall_start = (fl->res.y / 2) - (fl->rs[c_n].size / 2);
        i = 0;
        if (fl->rs[c_n].size > fl->res.y)
        {
            wall_start = 0;
            offset = (fl->rs[c_n].size - fl->res.y) / 2 / param;
        }
        while (i < fl->rs[c_n].size && (i < fl->res.y))
        {
            color = pixel_get(&tx, t_x, (offset + i / param));
            pixel_put(&fl->ml.img, c_n, (int)(wall_start + i), color);
            i++;
        }
    }
}

void cast_view(t_player *pl, t_cub *fl)
{
    float x;
    float y;
    int i;

    //		distance to projection plane
    fl->dist_plane = fl->res.x / 2 / tan(FOV / 2);
    pl->r_st = pl->pov - (FOV/2);
    pl->r_end = pl->pov + (FOV /2);

    i = 0;
    while (pl->r_st < pl->r_end)
    {
        x = pl->pos.x;
        y = pl->pos.y;
        while (fl->m.map_ar[(int)y][(int)x] != '1' )
        {
            x += cos(pl->r_st)/120;
            y += sin(pl->r_st)/120;

        }
        int dot = 0;
        double dx = cos(pl->r_st)/120;
        double dy = sin(pl->r_st)/120;
        while (dot < 20 )
        {
            if (fl->m.map_ar[(int)(y - dy/2)][(int)(x - dx/2)] == '1')
            {
                x -= dx/2;
                y -= dy/2;
            }
           else
            {
               dx /= 2;
               dy /= 2;
            }
           dot++;
        }

//		Hits which side
            fl->rs[i].r_pos.x = x;
            fl->rs[i].r_pos.y = y;

//		Distance and ray size
        fl->rs[i].dist = hypotf((fl->rs[i].r_pos.x - pl->pos.x),(fl->rs[i].r_pos.y - pl->pos.y)) * cosf(pl->pov - pl->r_st);
        fl->rs[i].size = (1 / fl->rs[i].dist  * fl->dist_plane);

        fl->rs[i].qdrnt = f_quadrant(fl->m.plr.r_st);
        if (fabs(fl->rs[i].r_pos.y - round(fl->rs[i].r_pos.y)) < fabs(fl->rs[i].r_pos.x - round(fl->rs[i].r_pos.x)))
        {
            fl->rs[i].hitx = 1;
            fl->rs[i].hity = 0;
            if ((fl->rs[i].qdrnt == 4) || (fl->rs[i].qdrnt == 3))
                draw_col(fl, fl->m.no, i);
            else
                draw_col(fl, fl->m.so, i);
        }
        else
        {
            fl->rs[i].hity = 1;
            fl->rs[i].hitx = 0;
            if ((fl->rs[i].qdrnt == 3 || fl->rs[i].qdrnt == 2) && fl->rs[i].hity == 1)
                draw_col(fl, fl->m.we, i);
            else
            draw_col(fl, fl->m.ea, i);
        }
        i++;
        pl->r_st += (float)(FOV) / fl->res.x;
    }
}

int    f_quadrant(double angle)
{
    int quadrant;

    if (cos(angle) > 0 && sin(angle) > 0)
        quadrant = 1;
    else if (sin(angle) > 0 && cos(angle) < 0)
        quadrant = 2;
    else if (cos(angle) > 0 && sin(angle) < 0)
        quadrant = 4;
    else quadrant = 3;
    return (quadrant);
}
//
//void dda_check(t_cub *fl)
//{
//
//}
