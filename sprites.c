#include "cub3d.h"

void sort_spr(t_cub *fl, t_spr *spr)
{
    t_spr temp;
    size_t i;

    i = 0;
    while (i < fl->sprs - 1)
    {
        if (spr[i].dist < spr[i + 1].dist)
        {
            temp = spr[i + 1];
            spr[i + 1] = spr[i];
            spr[i] = temp;
        }
        i++;
    }
}

void get_spr_info(t_fxy *pos, t_spr *spr, t_cub *fl)
{
    spr->dir = atan2(spr->xy.y - pos->y, spr->xy.x - pos->x) - fl->m.plr.pov;
    if (spr->dir > M_PI)
        spr->dir -= 2 * M_PI;
    if (spr->dir < -M_PI)
        spr->dir += 2 * M_PI;
    spr->dist = hypot((pos->x - spr->xy.x), (pos->y - spr->xy.y));
    spr->sz = (1 / spr->dist  * fl->dist_plane);
    spr->x_ofst = (fl->res.x / 2) + (spr->dir / (FOV/fl->res.x)) - (spr->sz/2);
    spr->y_ofst = (fl->res.y / 2) - (spr->sz / 2);
}

void draw_spr(t_spr *spr, t_cub *fl)
{
    size_t j;
    size_t z;

    unsigned int color;
    j = 0;

    while (j <= spr->sz)
    {
        if (spr->x_ofst + j < 0 || spr->x_ofst + j >= fl->res.x )
        {
            j++;
            continue;
        }
        z = 0;
        while (z < spr->sz)
        {
            if (spr->y_ofst + z < 0 || spr->y_ofst + z >= fl->res.y)
            {
                z++;
                continue;
            }
            color = pixel_get(&fl->m.sprite, (j * fl->m.sprite.hei /spr[0].sz), (z * fl->m.sprite.hei / spr[0].sz));
            if ((color & 0xFF000000) == 0 && fl->rs[(int)spr->x_ofst + j].dist > spr->dist)
                pixel_put(&fl->ml.img, spr->x_ofst + j,spr->y_ofst + z, color);
            z++;
        }
        j++;
    }
}
