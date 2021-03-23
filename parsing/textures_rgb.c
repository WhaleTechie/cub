/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:15:23 by lkrinova          #+#    #+#             */
/*   Updated: 2021/03/17 15:31:18 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_rgb(char *s)
{
	int i;

	i = 0;
	if (ft_strlen(s) > 3 || ft_strlen(s) < 1 )
		return (0);
	while(s[i] != '\0')
	{
		if (ft_isdigit(s[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

void get_r_rgb(char *s, t_cub *flags)
{
	char **rgb;
	char **arr;
	int r, g, b;

	arr = ft_split(s, ' ');
	if (s[0] == 'R')
	{
		flags->res.x = ft_atoi(arr[1]);
		flags->res.y = ft_atoi(arr[2]);
	}
	else if (s[0] == 'F')
	{
		rgb = ft_split(arr[1], ',');
		if (check_rgb(rgb[0]) != 1 || check_rgb(rgb[1]) != 1 || check_rgb
																		(rgb[2]) != 1)
		{
			ft_putstr_fd("Error: wrong RGB param of floor\n", 2);
			free_mass(rgb);
			exit (0);
		}
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		if ((r < 0) || (r > 255) || (g < 0) || (g > 255) || (b < 0) || (b >
																		255))
		{
			ft_putstr_fd("Error: wrong RGB param of floor\n", 2);
			free_mass(rgb);
			exit (0);
		}
		free_mass(rgb);
		flags->floor_rgb = (r << 16) + (g << 8) + b;
	}
	else
	{
		rgb = ft_split(arr[1], ',');
		if (check_rgb(rgb[0]) != 1 || check_rgb(rgb[1]) != 1 || check_rgb
																		(rgb[2]) != 1)
		{
			ft_putstr_fd("Error: wrong RGB param of ceiling\n", 2);
			free_mass(rgb);
			exit (0);
		}
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		if ((r < 0) || (r > 255) || (g < 0) || (g > 255) || (b < 0) || (b >
																		255))
		{
			ft_putstr_fd("Error: wrong RGB param of ceiling\n", 2);
			free_mass(rgb);
			exit (0);
		}
		free_mass(rgb);
		flags->ceil_col = (r << 16) + (g << 8) + b;
	}
	free_mass(arr);
}

void		get_texture(char *str, t_cub *flagg)
{
	char	**arr2;

	arr2 = ft_split(str, ' ');
	if (str[0] == 'N' && str[1] == 'O')
		flagg->no_tex = ft_strdup(arr2[1]);
	else if (str[0] == 'S' && str[1] == 'O')
		flagg->so_tex = ft_strdup(arr2[1]);
	else if (str[0] == 'W' && str[1] == 'E')
		flagg->we_tex = ft_strdup(arr2[1]);
	else if (str[0] == 'E' && str[1] == 'A')
		flagg->ea_tex = ft_strdup(arr2[1]);
	else if (str[0] == 'S')
		flagg->sprite = ft_strdup(arr2[1]);
	free_mass(arr2);
}
