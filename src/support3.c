/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 15:53:04 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	drawsprite(t_env *env, t_rend *rend, int j)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += R->csprya * WWIN + R->sprx;
	y = R->csprya - 1;
	while (++y <= R->cspryb)
	{
		txty = (int)((double)(y - R->sprya) /
			(double)(R->spryb - R->sprya) * ESJT0->h);
		if (y == HWIN / 2 && R->sprx == WWIN / 2 && env->sprite[j].type == 1 &&
			((int *)(ESJT0->pixels))[txty % ESJT0->h * ESJT0->w + R->txtx] != 0)
			env->player.target = j;
		if (((int *)(ESJT0->pixels))[txty % ESJT0->h * ESJT0->w + R->txtx] != 0)
			*pix = ((int *)(ESJT0->pixels))[txty %
				ESJT0->h * ESJT0->w + R->txtx];
		pix += WWIN;
	}
}

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
