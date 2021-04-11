/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 20:11:11 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/06 17:15:35 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Making map array
*/

void		get_map(char **arr, t_cub *flags)
{
	int		i;
	int		k;

	i = flags->allmap.m_start;
	if (!(flags->allmap.map_ar = (char **)malloc((flags->allmap.size.y
												 + 1) * sizeof(char*))))
		ft_putstr_fd("Error in mallocing array", 2);
	k = 0;
	while (arr[i] != 0)
	{
		flags->allmap.map_ar[k] = ft_strdup(arr[i]);
		k++;
		i++;
	}
	flags->allmap.map_ar[k] = 0;
}

void		get_param(char **arr, t_cub *flags)
{
	int		i;
	int		y;

	i = -1;
	while (arr[++i] != 0)
	{
		if (arr[i][0] == 'R' || arr[i][0] == 'F' || arr[i][0] == 'C')
			get_r_rgb(arr[i], flags);
		else if (((arr[i][0] == 'N' || arr[i][0] == 'S') && arr[i][1] == 'O')
				 || (arr[i][0] == 'W' && arr[i][1] == 'E') || (arr[i][0] == 'E'
															   && arr[i][1] == 'A') || (arr[i][0] == 'S' && arr[i][1] == ' '))
			get_texture(arr[i], flags);
		else if (arr[i][0] == ' ' || arr[i][0] == '1')
		{
			if (flags->allmap.size.y == 0)
				flags->allmap.m_start = i;
			flags->allmap.size.y++;
			y = 0;
			while (arr[i][y] != '\0')
				y++;
			if (y > flags->allmap.size.x)
				flags->allmap.size.x = y;
		}
	}
}


void get_text(t_cub *fl)
{
	if ((fl->allmap.no.image = mlx_xpm_file_to_image(fl->ml.mlx_ptr,
												  fl->no_tex,&fl->allmap.no
												  .width, &fl->allmap.no.height)))
		fl->allmap.no.addr = mlx_get_data_addr(fl->allmap.no.image, &fl->allmap.no
		.bpp, &fl->allmap.no.size_line, &fl->allmap.no.endian);
	if ((fl->allmap.so.image = mlx_xpm_file_to_image(fl->ml.mlx_ptr,
												 fl->so_tex,&fl->allmap.so.width, &fl->allmap.so.height)))
		fl->allmap.so.addr = mlx_get_data_addr(fl->allmap.so.image,
										 &fl->allmap.so.bpp,&fl->allmap.so.size_line, &fl->allmap.so.endian);
	if ((fl->allmap.we.image = mlx_xpm_file_to_image(fl->ml.mlx_ptr,
												  fl->we_tex,&fl->allmap.we
												  .width, &fl->allmap.we.height)))
		fl->allmap.we.addr = mlx_get_data_addr(fl->allmap.we.image,
										 &fl->allmap.we.bpp,&fl->allmap.we.size_line, &fl->allmap.we.endian);
	if ((fl->allmap.ea.image = mlx_xpm_file_to_image(fl->ml.mlx_ptr,
												  fl->ea_tex,&fl->allmap.ea
												  .width, &fl->allmap.ea.height)))
		fl->allmap.ea.addr = mlx_get_data_addr(fl->allmap.ea.image,
										 &fl->allmap.ea.bpp,&fl->allmap.ea.size_line, &fl->allmap.ea.endian);
	if ((fl->allmap.sprite.image = mlx_xpm_file_to_image(fl->allmap.sprite.image,
													  fl->sprite, &fl->allmap
													  .sprite.width, &fl->allmap.sprite.height)))
		fl->allmap.sprite.addr = mlx_get_data_addr(fl->ml.mlx_ptr, &fl->allmap.sprite.bpp, &fl->allmap.sprite.size_line, &fl->allmap.sprite.endian);
}

void		parse(char *buffer, t_cub *flags)
{
	char	**arr_cub;

	arr_cub = ft_split(buffer, '\n');
	get_param(arr_cub, flags);
	get_map(arr_cub, flags);
	find_player(flags->allmap.map_ar, flags);
//	get_text(flags);
	flags->dist_plane = flags->res.x / 2 / tan((FOV/2));
	free_mass(arr_cub);
}
