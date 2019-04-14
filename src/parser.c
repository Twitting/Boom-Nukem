/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:23:00 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 20:15:12 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	neighborstosect(t_sector *sect, char *line, int i)
{
	int	count;

	count = 0;
	while (line[i] != '\0')
	{
		sect->neighbors[count] = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i] != '\0')
			i++;
		count++;
		if (line[i] == '\0')
			break ;
		i++;
	}
}

void	verttosect(t_env *env, t_sector *sect, char *line, int i)
{
	int	j;
	int count;

	count = 0;
	i++;
	j = i;
	sect->npoints = 1;
	while (line[j] != '\t')
	{
		if (line[j] == ' ')
			sect->npoints++;
		j++;
	}
	sect->neighbors = (int *)malloc(sizeof(int) * sect->npoints);
	sect->vertex = (t_xy *)malloc(sizeof(t_xy) * sect->npoints);
	while (line[i] != '\t')
	{
		sect->vertex[count] = env->vertex[ft_atoi(&line[i])];
		while (line[i] != ' ' && line[i] != '\t')
			i++;
		count++;
		i++;
	}
	neighborstosect(sect, line, i);
}

void	playerinit(t_env *env)
{
	env->player.velocity.x = 0.0;
	env->player.velocity.y = 0.0;
	env->player.velocity.z = 0.0;
	env->player.yaw = 0.0;
	env->player.keys = 0;
	env->player.pushingbutton = 0;
	EPW.z = ESEC[EPS].floor + EYEHEIGHT;
	env->player.hp = 100;
	env->player.eye = EYEHEIGHT;
}

void	parseplayer(t_env *env, int fd)
{
	int		i;
	char	*line;

	get_next_line(fd, &line);
	i = 0;
	while (line[i] != '\t')
		i++;
	EPW.x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	EPW.y = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	PANG = (ft_atoi(&line[i]) % 360) * M_PI / 180;
	while (line[i] != ' ')
		i++;
	EPS = ft_atoi(&line[i]);
	playerinit(env);
	free(line);
	if (get_next_line(fd, &line))
		free(line);
}

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

void	parsesprites_support(t_env *env, int count, char *line, int *i)
{
	(*i) += 7;
	env->sprite[count].pos1.x = ft_atoi(&line[(*i)]);
	while (line[(*i)] != ' ')
		(*i)++;
	env->sprite[count].pos1.y = ft_atoi(&line[(*i)]);
	while (line[(*i)] != '\t')
		(*i)++;
	env->sprite[count].type = ft_atoi(&line[(*i)]);
	while (line[(*i)] != ' ')
		(*i)++;
	env->sprite[count].sector = ft_atoi(&line[(*i)]);
}

int		parsesprites(t_env *env, int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		if (line[0] == 'o')
		{
			parsesprites_support(env, count, line, &i);
			count++;
		}
		else if (line[0] != 'o' && line[0] == '\0')
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (count);
}

void	spritemaker(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (ESPRI.type == 0 || ESPRI.type == 3)
		{
			ESPRI.height = 7;
			ESPRI.width = 3;
		}
		else if (ESPRI.type == 1)
		{
			ESPRI.height = 12;
			ESPRI.width = 4;
		}
		else if (ESPRI.type >= 5)
		{
			ESPRI.height = 6;
			ESPRI.width = 1;
		}
	}
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
	ESPRI.height = MIN(ESEC[env->wallsp.sect1].ceiling, ESEC[env->wallsp.sect2].ceiling);
	ESPRI.floor = MAX(ESEC[env->wallsp.sect1].floor, ESEC[env->wallsp.sect2].floor);
	ESPRI.type = 2;
	ESPRI.texture[0] = IMG_Load("textures/bars.png");
	env->sprite[i + 1].height = MIN(ESEC[env->wallsp.sect1].ceiling, ESEC[env->wallsp.sect2].ceiling);
	env->sprite[i + 1].floor = MAX(ESEC[env->wallsp.sect1].floor, ESEC[env->wallsp.sect2].floor);
	env->sprite[i + 1].type = 2;
	env->sprite[i + 1].texture[0] = IMG_Load("textures/bars.png");
	ESPRI.openbar = 0;
	env->sprite[i + 1].openbar = 0;
	ESPRI.visible = 1;
	env->sprite[i + 1].visible = 1;
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
