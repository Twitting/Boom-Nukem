/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:25:09 by twitting          #+#    #+#             */
/*   Updated: 2019/04/11 21:05:01 by daharwoo         ###   ########.fr       */
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

void	parseplayer(t_env *env, int fd)
{
	int		i;
	char	*line;

	get_next_line(fd, &line);
	i = 0;
	while (line[i] != '\t')
		i++;
	env->player.where.x = ft_atoi(&line[i]);
	while (line[i] != ' ')
		i++;
	env->player.where.y = ft_atoi(&line[i]);
	while (line[i] != '\t')
		i++;
	env->player.angle = (ft_atoi(&line[i]) % 360) * M_PI / 180;
	while (line[i] != ' ')
		i++;
	env->player.sector = ft_atoi(&line[i]);
	env->player.velocity.x = 0.0;
	env->player.velocity.y = 0.0;
	env->player.velocity.z = 0.0;
	env->player.yaw = 0.0;
	env->player.where.z = env->sector[env->player.sector].floor + EYEHEIGHT;
	free(line);
	if (get_next_line(fd, &line))
		free(line);
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
			i += 7;
			env->sector[count].sky = 0;
			env->sector[count].floor = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sector[count].ceiling = ft_atoi(&line[i]);
			if (env->sector[count].ceiling < 0)
			{
				env->sector[count].ceiling *= -1;
				env->sector[count].sky = 1;
			}
			while (line[i] != '\t')
				i++;
			env->sector[count].light = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sector[count].textpack = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			verttosect(env, &env->sector[count], line, i);
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
		ft_putstr("openerr\n");
	while (get_next_line(fd, &line) > 0)
	{
		getvertsectnums_support(env, line);
		free(line);
	}
	close(fd);
	env->sector = (t_sector *)malloc(sizeof(t_sector) * (env->nsectors));
	env->vertex = (t_xy *)malloc(sizeof(t_xy) * env->nvertexes);
	env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * env->sprcount);
	env->button = (t_button *)malloc(sizeof(t_button) * env->nsectors);
	if (!env->sector || !env->vertex || !env->sprite || !env->button)
		ft_error(2);
}

int	parsesprites(t_env *env, int fd)
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
			i += 7;
			env->sprite[count].pos1.x = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sprite[count].pos1.y = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			env->sprite[count].type = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sprite[count].sector = ft_atoi(&line[i]);
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
		if (env->sprite[i].type == 0)
		{
			env->sprite[i].height = 7;
			env->sprite[i].width = 3;
		}
		else if (env->sprite[i].type == 1)
		{
			env->sprite[i].height = 12;
			env->sprite[i].width = 4;
		}
	}
}

void	makewallsp(t_env *env, int i)
{
	env->sprite[i].pos1.x = env->vertex[env->wallsp.vert1].x;
	env->sprite[i].pos1.y = env->vertex[env->wallsp.vert1].y;
	env->sprite[i + 1].pos1.x = env->vertex[env->wallsp.vert2].x;
	env->sprite[i + 1].pos1.y = env->vertex[env->wallsp.vert2].y;
	env->sprite[i].pos2.x = env->vertex[env->wallsp.vert2].x;
	env->sprite[i].pos2.y = env->vertex[env->wallsp.vert2].y;
	env->sprite[i + 1].pos2.x = env->vertex[env->wallsp.vert1].x;
	env->sprite[i + 1].pos2.y = env->vertex[env->wallsp.vert1].y;
	env->sprite[i].sector = env->wallsp.sect2;
	env->sprite[i + 1].sector = env->wallsp.sect1;
	env->sprite[i].height = MIN(env->sector[env->wallsp.sect1].ceiling, env->sector[env->wallsp.sect2].ceiling);
	env->sprite[i].floor = MAX(env->sector[env->wallsp.sect1].floor, env->sector[env->wallsp.sect2].floor);
	env->sprite[i].type = 2;
	env->sprite[i].texture[0] = IMG_Load("textures/bars.png");
	env->sprite[i + 1].height = MIN(env->sector[env->wallsp.sect1].ceiling, env->sector[env->wallsp.sect2].ceiling);
	env->sprite[i + 1].floor = MAX(env->sector[env->wallsp.sect1].floor, env->sector[env->wallsp.sect2].floor);
	env->sprite[i + 1].type = 2;
	env->sprite[i + 1].texture[0] = IMG_Load("textures/bars.png");
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
			i += 7;
			env->wallsp.vert1 = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->wallsp.vert2 = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			env->wallsp.sect1 = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->wallsp.sect2 = ft_atoi(&line[i]);
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
		ft_putstr("openerr\n");

	getvertsectnums(env);
	parsevertexes(env, fd);
	parsesectors(env, fd);
	parseplayer(env, fd);
	sprites = parsesprites(env, fd);
	parsewallsps(env, fd, sprites);
	spritemaker(env);
	close(fd);
}
