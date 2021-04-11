/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <lkrinova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:26:16 by lkrinova          #+#    #+#             */
/*   Updated: 2021/01/11 16:13:13 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strcat(char *s1, const char *s2)
{
	int			i;
	int			j;

	i = 0;
	while (s1[i] != '\0')
		i++;
	j = 0;
	while (s2[j] != '\0')
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}

char			*ft_strcpy(char *dest, const char *src)
{
	int			i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*check_left(char **left, char **line)
{
	char		*pn;

	pn = NULL;
	if (*left)
	{
		if ((pn = ft_strchr(*left, '\n')))
		{
			*pn = '\0';
			*line = ft_strdup(*left);
			ft_strcpy(*left, ++pn);
		}
		else
		{
			*line = ft_strdup(*left);
			free(*left);
			*left = NULL;
		}
	}
	else
		*line = ft_strnew(1);
	return (pn);
}

int				get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	int			byte_read;
	char		*pn;
	static char	*left = NULL;
	char		*tmp;

	if (read(fd, NULL, 0) == -1)
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	pn = check_left(&left, line);
	while (!pn && ((byte_read = (read(fd, buffer, BUFFER_SIZE))) > 0))
	{
		buffer[byte_read] = '\0';
		if ((pn = ft_strchr(buffer, '\n')))
		{
			*pn = '\0';
			pn++;
			left = ft_strdup(pn);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	return (byte_read || left) ? 1 : 0;
}
