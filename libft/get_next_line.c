/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:06:21 by twitting          #+#    #+#             */
/*   Updated: 2018/12/20 19:34:43 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	line_formation(char **line, char **str, const int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((tmp = ft_strchr(str[fd], '\n')))
	{
		if (!(tmp = ft_strdup(tmp + 1)))
			return (-1);
		while (str[fd][i] != '\n')
			i++;
		if (!(*line = ft_strsub(str[fd], 0, i)))
			return (-1);
		free(str[fd]);
		if (!(tmp))
			str[fd] = NULL;
		else
			str[fd] = tmp;
	}
	else
	{
		*line = ft_strsub(str[fd], 0, ft_strlen(str[fd]));
		free(str[fd]);
		str[fd] = 0;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str[65536];
	char		buff[BUFF_SIZE + 1];
	ssize_t		readed;
	char		*tmp;

	if (line == NULL || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	while (0 < (readed = read(fd, buff, BUFF_SIZE)))
	{
		if (!(str[fd]))
			if (!(str[fd] = ft_strnew(0)))
				return (-1);
		buff[readed] = '\0';
		if (!(tmp = ft_strjoin(str[fd], buff)))
			return (-1);
		free(str[fd]);
		str[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			return (line_formation(line, str, fd));
	}
	if (readed < 0)
		return (-1);
	if (!(str[fd]) || ((str[fd][0]) == 0 && readed == 0))
		return (0);
	return (line_formation(line, str, fd));
}
