/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 15:54:35 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	parsesectors_support(t_env *env, int count, char *line, int *i)
{
	(*i) += 7;
	ESEC[count].sky = 0;
	ESEC[count].floor = ft_atoi(&line[*i]);
	while (line[*i] != ' ')
		(*i)++;
	ESEC[count].ceiling = ft_atoi(&line[*i]);
	if (ESEC[count].ceiling < 0)
	{
		ESEC[count].ceiling *= -1;
		ESEC[count].sky = 1;
	}
	while (line[*i] != '\t')
		(*i)++;
	ESEC[count].light = ft_atoi(&line[*i]);
	ESEC[count].on = ESEC[count].light > 40 ? 1 : 0;
	while (line[*i] != ' ')
		(*i)++;
	ESEC[count].textpack = ft_atoi(&line[*i]);
	while (line[*i] != '\t')
		(*i)++;
}

void	parsesectors(t_env *env, int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 's')
		{
			parsesectors_support(env, count, line, &i);
			verttosect(env, &ESEC[count], line, i);
		}
		else if (line[0] != 's')
		{
			free(line);
			break ;
		}
		free(line);
		count++;
	}
}

void	parsevertexes(t_env *env, int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 'v')
		{
			i += 7;
			env->vertex[count].y = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			env->vertex[count].x = ft_atoi(&line[i]);
		}
		else if (line[0] != 'v')
		{
			free(line);
			break ;
		}
		free(line);
		count++;
	}
}

void	getvertsectnums_support(t_env *env, char *line)
{
	if (line[0] == 'v')
		env->nvertexes++;
	else if (line[0] == 's')
		env->nsectors++;
	else if (line[0] == 'o')
		env->sprcount++;
	else if (line[0] == 'w')
		env->sprcount += 2;
}

void	getvertsectnums(t_env *env)
{
	int		fd;
	char	*line;

	env->nsectors = 0;
	env->nvertexes = 0;
	env->sprcount = 0;
	if ((fd = open(env->mapname, O_RDONLY)) < 0)
		ft_error(3);
	while (get_next_line(fd, &line) > 0)
	{
		getvertsectnums_support(env, line);
		free(line);
	}
	close(fd);
	ESEC = (t_sector *)malloc(sizeof(t_sector) * (env->nsectors));
	env->vertex = (t_xy *)malloc(sizeof(t_xy) * env->nvertexes);
	env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * env->sprcount);
	env->button = (t_button *)malloc(sizeof(t_button) * env->nsectors);
	if (!ESEC || !env->vertex || !env->sprite || !env->button)
		ft_error(2);
}
