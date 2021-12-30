/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshantay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:29:14 by kshantay          #+#    #+#             */
/*   Updated: 2021/12/30 15:20:25 by kshantay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_free(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	ft_read_line(char *buf, char **line)
{
	int		i;
	int		j;
	int		flag;
	char	*search_line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag = 0;
	if (buf[i] == '\n')
		flag = 1;
	search_line = ft_calloc(i + flag + 1, 1);
	if (search_line == NULL)
		return (-1);
	while (j < i + flag)
	{
		search_line[j] = buf[j];
		j++;
	}
	*line = ft_strjoin(*line, search_line);
	if (*line == NULL)
		return (-1);
	ft_strcpy(buf, &buf[i + flag]);
	return (flag);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			count_byte;
	int			flag;

	line = NULL;
	flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (flag == 0)
	{
		flag = ft_read_line(buf, &line);
		if (flag == -1)
			return (ft_free(&line));
		else if (flag == 0)
		{
			count_byte = read(fd, buf, BUFFER_SIZE);
			if (count_byte == 0 && *line)
				flag = 1;
			else if (count_byte <= 0)
				return (ft_free(&line));
			buf[count_byte] = '\0';
		}
	}
	return (line);
}
