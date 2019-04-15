/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:23:00 by twitting          #+#    #+#             */
/*   Updated: 2019/04/15 15:57:15 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	makewallsp_support(t_env *env, int i)
{
	env->sprite[i + 1].height = MIN(ESEC[env->wallsp.sect1].ceiling,
			ESEC[env->wallsp.sect2].ceiling);
	env->sprite[i + 1].floor = MAX(ESEC[env->wallsp.sect1].floor,
			ESEC[env->wallsp.sect2].floor);
	env->sprite[i + 1].type = 2;
	env->sprite[i + 1].texture[0] = IMG_Load("textures/bars.png");
	ESPRI.openbar = 0;
	env->sprite[i + 1].openbar = 0;
	ESPRI.visible = 1;
	env->sprite[i + 1].visible = 1;
}

void	makewallsp(t_env *env, int i)
{
	ESPRI.pos1.x = env->vertex[env->wallsp.vert1].x;
	ESPRI.pos1.y = env->vertex[env->wallsp.vert1].y;
	env->sprite[i + 1].pos1.x = env->vertex[env->wallsp.vert2].x;
	env->sprite[i + 1].pos1.y = env->vertex[env->wallsp.vert2].y;
	ESPRI.pos2.x = env->vertex[env->wallsp.vert2].x;
	ESPRI.pos2.y = env->vertex[env->wallsp.vert2].y;
	env->sprite[i + 1].pos2.x = env->vertex[env->wallsp.vert1].x;
	env->sprite[i + 1].pos2.y = env->vertex[env->wallsp.vert1].y;
	ESPRI.sector = env->wallsp.sect2;
	env->sprite[i + 1].sector = env->wallsp.sect1;
	ESPRI.height = MIN(ESEC[env->wallsp.sect1].ceiling,
			ESEC[env->wallsp.sect2].ceiling);
	ESPRI.floor = MAX(ESEC[env->wallsp.sect1].floor,
			ESEC[env->wallsp.sect2].floor);
	ESPRI.type = 2;
	ESPRI.texture[0] = IMG_Load("textures/bars.png");
	makewallsp_support(env, i);
}

void	parsewallsps_support(t_env *env, char *line, int *i)
{
	(*i) += 7;
	env->wallsp.vert1 = ft_atoi(&line[(*i)]);
	while (line[(*i)] != ' ')
		(*i)++;
	env->wallsp.vert2 = ft_atoi(&line[(*i)]);
	while (line[(*i)] != '\t')
		(*i)++;
	env->wallsp.sect1 = ft_atoi(&line[(*i)]);
	while (line[(*i)] != ' ')
		(*i)++;
	env->wallsp.sect2 = ft_atoi(&line[(*i)]);
}

void	parsewallsps(t_env *env, int fd, int count)
{
	char	*line;
	int		i;

	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 'w')
		{
			parsewallsps_support(env, line, &i);
			makewallsp(env, count);
			count += 2;
		}
		else if (line[0] != 'w')
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	grandparser(t_env *env)
{
	int	fd;
	int	sprites;

	if ((fd = open(env->mapname, O_RDONLY)) < 0)
		ft_error(3);
	getvertsectnums(env);
	if (env->nvertexes < 3 || env->nsectors < 1)
		ft_error(3);
	parsevertexes(env, fd);
	parsesectors(env, fd);
	parseplayer(env, fd);
	if (env->player.where.x == 0)
		ft_error(3);
	sprites = parsesprites(env, fd);
	parsewallsps(env, fd, sprites);
	spritemaker(env);
	close(fd);
}
