/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 16:00:42 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

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

void	trintersect2(t_rend *rend, t_env *env, int j)
{
	if (R->ttr1.y < R->nfz.x)
	{
		if (R->i1.y > 0)
			R->ttr1 = R->i1;
		else
			R->ttr1 = R->i2;
	}
	if (R->ttr2.y < R->nfz.x)
	{
		if (R->i1.y > 0)
			R->ttr2 = R->i1;
		else
			R->ttr2 = R->i2;
	}
	if (fabs(R->ttr2.x - R->ttr1.x) > fabs(R->ttr2.y - R->ttr1.y))
	{
		R->u0 = (R->ttr1.x - RO1.x) * (ESJT0->w - 1) / (RO2.x - RO1.x);
		R->u1 = (R->ttr2.x - RO1.x) * (ESJT0->w - 1) / (RO2.x - RO1.x);
	}
	else
	{
		R->u0 = (R->ttr1.y - RO1.y) * (ESJT0->w - 1) / (RO2.y - RO1.y);
		R->u1 = (R->ttr2.y - RO1.y) * (ESJT0->w - 1) / (RO2.y - RO1.y);
	}
}

void	trintersect(t_rend *rend, t_env *env, int j)
{
	if (R->ttr1.y <= 0 || R->ttr2.y <= 0)
	{
		R->nfz.x = 1e-4;
		R->nfz.y = 5;
		R->nfside.x = 1e-5;
		R->nfside.y = 20;
		R->wintsect1.x = -R->nfside.x;
		R->wintsect1.y = R->nfz.x;
		R->wintsect2.x = -R->nfside.y;
		R->wintsect2.y = R->nfz.y;
		R->i1 = intersect(R->ttr1, R->ttr2, R->wintsect1, R->wintsect2);
		R->wintsect1.x = R->nfside.x;
		R->wintsect2.x = R->nfside.y;
		R->i2 = intersect(R->ttr1, R->ttr2, R->wintsect1, R->wintsect2);
		RO1 = (t_xy){R->ttr1.x, R->ttr1.y};
		RO2 = (t_xy){R->ttr2.x, R->ttr2.y};
		trintersect2(R, env, j);
	}
}
