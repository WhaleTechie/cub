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

int	ft_strcmp(char const *s1, char const *s2)
{
    while (*s1 || *s2)
        if (*s1++ != *s2++)
            return (*(s1 - 1) - *(s2 - 1));
    return (0);
}
void free_mass(char **mass)
{
	char **start = mass;
	while (*mass != NULL)
		free(*mass++);
	free(start);
}

char *read_cub(char *file)
{
    int fd;
    char buffer[4097];
    int byte_read;
    char *str;

    check_map_f(file);
    fd = open(file, O_RDONLY);
    // b_r = 1 if bt < 0
    if ((byte_read = read(fd, buffer, 4096)) < 0)
        ft_putstr_fd("Error in reading file \n", 2);
    buffer[byte_read] = '\0';
    str = ft_strdup(buffer);
//		strjoin пока рид не ноль
    return(str);
}

void mlx_engine(t_cub *flags)
{
//    int n;

    flags->ml.ml_p = mlx_init();
    flags->ml.w_p = mlx_new_window(flags->ml.ml_p, flags->res.x,
                                  flags->res.y, "Game Window");
//    flags->ml.img.im = mlx_new_image(flags->ml.ml_p, flags->res.x, flags->res.y);
//    flags->ml.img.addr = mlx_get_data_addr(flags->ml.img.im, &n, &n, &n);
    flags->ml.img.size_x = flags->res.x;
    flags->ml.img.size_y = flags->res.y;
    rays_arr_init(flags);

    get_text(flags);
    mlx_loop_hook(flags->ml.ml_p, render, (void *)flags);
    mlx_hook(flags->ml.w_p, 2, 1L << 0, move, (void *)flags);
    mlx_loop(flags->ml.ml_p);
}

int main(int argc, char **argv)
{
    t_cub flags;
    char    *cub_str;


	if (argc == 2)
	{
	    cub_str = read_cub(argv[1]);
        ft_bzero(&flags, sizeof(t_cub));
        parse(cub_str, &flags);
        mlx_engine(&flags);
	}
//	else if (argc == 3 && (ft_strcmp(argv[3], "--save") == 0))
//    {
//        cub_str = read_cub(argv[1]);
//        ft_bzero(&flags, sizeof(t_cub));
//        parse(cub_str, &flags);
//        mlx_engine(&flags);
//
//    }
	else
	    write(2,"Error: invalid number of args\n",30);
//	free(flags.m.map_ar);
	return (0);
}
