/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 15:43:23 by lkrinova          #+#    #+#             */
/*   Updated: 2021/03/17 18:15:45 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Check if it's a .cub file
*/

char 	*check_map_f(char *str)
{
	int len;

	len = ft_strlen(str);
	if ((len <= 4) || ft_strncmp((str + (len - 4)), ".cub", len) != 0)
	{
		ft_putstr_fd("Error:\n wrong cub filename\n", 2);
		str = NULL;
	}
	return (str);
}

/*
** Check map borders. 0 - not valid map
*/

int bad_sosed(char **arr, int i, int j)
{
	if (!arr[i][j] || arr[i][j] == '\0' || arr[i][j] == ' ')
		return (1);
	return (0);
}

int 	is_valid(char **ar)
{
	int i;
	int j;

	i = 0;
	while (ar[i] != 0)
	{
		j = 0;
		while (ar[i][j] != '\0')
		{
			if (ar[i][j] == '0' || ar[i][j] == '2' || ar[i][j] == 'N'
				|| ar[i][j] == 'S' || ar[i][j] == 'W' || ar[i][j] == 'E')
			{
				if (bad_sosed(ar, (i - 1), (j - 1)) == 1)
					return (0);
				if (bad_sosed(ar, (i - 1), j) == 1)
					return (0);
				if (bad_sosed(ar, (i - 1), (j + 1)) == 1)
					return (0);
				if (bad_sosed(ar, i, (j - 1)) == 1)
					return (0);
				if (bad_sosed(ar, i, (j + 1)) == 1)
					return (0);
				if (bad_sosed(ar, (i + 1), (j - 1)) == 1)
					return (0);
				if (bad_sosed(ar, (i + 1), j) == 1)
					return (0);
				if (bad_sosed(ar, (i + 1), (j + 1)) == 1)
					return (0);
			}
			else
			{
				if (ar[i][j] != '1' && ar[i][j] != ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void 	find_player(char **ar, t_cub *flags)
{
	int i;
	int j;

	i = 0;
	while (ar[i] != 0)
	{
		j = 0;
		while (ar[i][j] != '\0')
		{
			if (ar[i][j] == 'N' || ar[i][j] == 'S' || ar[i][j] == 'W' ||
				ar[i][j] == 'E')
			{
				if (flags->allmap.player.pos.x != 0)
					ft_putstr_fd("Error\nMore than one player on the map\n",
								 2);
				flags->allmap.player.pos.x = (float)j + 0.5f;
				flags->allmap.player.pos.y = (float)i + 0.5f;
				flags->allmap.player.pov = get_pov(ar[i][j]);
			}
			j++;
		}
		i++;
	}
}
