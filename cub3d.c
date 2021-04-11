/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:44:32 by lkrinova          #+#    #+#             */
/*   Updated: 2021/04/06 13:55:39 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minilibx_opengl/mlx.h"

void free_mass(char **mass)
{
	char **start = mass;
	while (*mass != NULL)
		free(*mass++);
	free(start);
}


int main(int argc, char **argv)
{
	int fd;
	t_cub flags;
	char buffer[4097];
	int byte_read;
	int n;

	if (argc == 2)
	{
		check_map_f(argv[1]);
		fd = open(argv[1], O_RDONLY);
		if ((byte_read = read(fd, buffer, 4096)) < 0)
			ft_putstr_fd("Error in reading file \n", 2);
		buffer[byte_read] = '\0';
		ft_bzero(&flags, sizeof(t_cub));
		parse(buffer, &flags);


/*
** MiniLibx part
*/

		flags.ml.mlx_ptr = mlx_init();
		flags.ml.win_ptr = mlx_new_window(flags.ml.mlx_ptr, flags.res.x,
										  flags.res.y,"Game Window");
		flags.ml.img.im = mlx_new_image(flags.ml.mlx_ptr, flags.res.x, flags
				.res.y);
		flags.ml.img.size_x = flags.res.x;
		flags.ml.img.size_y = flags.res.y;
		rays_arr_init(&flags);
		flags.ml.img.addr = mlx_get_data_addr(flags.ml.img.im, &n, &n, &n);
		get_text(&flags);
		mlx_loop_hook(flags.ml.mlx_ptr, render, (void *)&flags);
		mlx_hook(flags.ml.win_ptr, 2, 1L<<0, move, &flags);
		mlx_loop(flags.ml.mlx_ptr);

/*
** Checking ------ TO DELETE ----------
*/

//		printf("x= %d\n", flags.res.x);
//		printf("y= %d\n", flags.res.y);
		printf("NO texture= %s\n", flags.no_tex);
		printf("SO texture= %s\n", flags.so_tex);
		printf("WE texture= %s\n", flags.we_tex);
		printf("EA texture= %s\n", flags.ea_tex);
		printf("Sprite texture= %s\n", flags.sprite);
		printf("RGB floor = %d\n", flags.floor_rgb);
		printf("RGB ceiling = %d\n", flags.ceil_col);
		printf("Start of the map = %d\n", flags.allmap.m_start);
//		printf("Number of lines = %d\n", flags.allmap.size.x);
//		printf("Number of columns = %d\n", flags.allmap.size.y);
		printf("Map\n");
		int m = 0;
		while (flags.allmap.map_ar[m] != 0)
		{
			printf("%s\n", flags.allmap.map_ar[m]);
			m++;
		}
		if (is_valid(flags.allmap.map_ar) == 1)
			printf("Valid map!!\n");
		else
			printf("Not Valid map!!\n");
		printf("Player position x= %f\n y = %f\n", flags.allmap
				.player.pos.x, flags.allmap.player.pos.y);

	}
	else
		write(2,"Error: invalid number of args\n",30);
//	free(flags.allmap.map_ar);
	return (0);
}
