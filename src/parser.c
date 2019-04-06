/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:25:09 by twitting          #+#    #+#             */
/*   Updated: 2019/04/06 20:18:57 by twitting         ###   ########.fr       */
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
	int	i;
	char *line;

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
	ft_putnbr(env->player.sector);
	env->player.velocity.x = 0.0;
	env->player.velocity.y = 0.0;
	env->player.velocity.z = 0.0;
	env->player.yaw = 0.0;
	env->player.where.z = env->sector[env->player.sector].floor + EYEHEIGHT;
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
			//env->sector[count].sky = 0;
			env->sector[count].floor = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sector[count].ceiling = ft_atoi(&line[i]);
			if (env->sector[count].ceiling < 0)
			{
				env->sector[count].ceiling *= -1;
				//env->sector[count].sky = 1;
			}
			while (line[i] != '\t')
				i++;
			env->sector[count].light = ft_atoi(&line[i]);
			while (line[i] != ' ')
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
		if (line[0] == 'v')
			env->nvertexes++;
		else if (line[0] == 's')
			env->nsectors++;
		else if (line[0] == 'o')
			env->sprcount++;
		free(line);
	}
	close(fd);
	env->sector = (t_sector *)malloc(sizeof(t_sector) * (env->nsectors));
	env->vertex = (t_xy *)malloc(sizeof(t_xy) * env->nvertexes);
	env->sprite = (t_sprite *)malloc(sizeof(t_sprite) * env->sprcount);
	if (!env->sector || !env->vertex || !env->sprite)
		ft_error(2);
}

void	parsesprites(t_env *env, int fd)
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
			env->sprite[count].x = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sprite[count].y = ft_atoi(&line[i]);
			while (line[i] != '\t')
				i++;
			env->sprite[count].type = ft_atoi(&line[i]);
			while (line[i] != ' ')
				i++;
			env->sprite[count].sector = ft_atoi(&line[i]);
			count++;
		}
		else if (line[0] != 'o' && line[0] != '\0')
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	spritelightapply(t_env *env, t_sprite *sprite)
{
	int j;
	int k;
	unsigned char *pix;
	
	sprite->texture = sprite->type == 0 ? IMG_Load("textures/barrel.png") : IMG_Load("textures/enemy.png");
	pix = (unsigned char *)sprite->texture->pixels;
	j = -1;
	while (++j < sprite->texture->h)
	{
		k = -1;
		while (++k < sprite->texture->w - 1)
		{
			pix[(j * sprite->texture->w + k) * 4] = (unsigned char)((double)pix[(j * sprite->texture->w + k) * 4] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture->w + k) * 4 + 1] = (unsigned char)((double)pix[(j * sprite->texture->w + k) * 4 + 1] / 100 * env->sector[sprite->sector].light);
			pix[(j * sprite->texture->w + k) * 4 + 2] = (unsigned char)((double)pix[(j * sprite->texture->w + k) * 4 + 2] / 100 * env->sector[sprite->sector].light);
		}
	}
	env->fps++;
}

void	spritemaker(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
	{
		if (env->sprite[i].type == 0)
		{
			env->sprite[i].height = 12;
			env->sprite[i].width = 4;
		}
		else
		{
			env->sprite[i].height = 20;
			env->sprite[i].width = 7;
		}
		
	}
}

void	grandparser(t_env *env)
{
	int				fd;

	if ((fd = open(env->mapname, O_RDONLY)) < 0)
		ft_putstr("openerr\n");
	getvertsectnums(env);
	parsevertexes(env, fd);
	parsesectors(env, fd);
	parseplayer(env, fd);
	parsesprites(env, fd);
	spritemaker(env);
	close(fd);
}
