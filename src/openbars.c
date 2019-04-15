/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openbars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:30:58 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 12:44:31 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int		openbars(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
		if (ESPRI.openbar == 0 && ESPRI.type == 2 &&
		ESPRI.sector == (int)EPS)
			if (ESPRI.spritedist <= 10)
			{
				ESPRI.openbar = 1;
				if (env->sprite[i + 1].type == 2)
					env->sprite[i + 1].openbar = 1;
				if (env->sprite[i - 1].type == 2)
					env->sprite[i - 1].openbar = 1;
				return (1);
			}
	return (0);
}

void	barsanimate2(t_env *env, int i)
{
	t_xy	xy;

	xy.x = ESPRI.pos2.x - 0.3;
	if (xy.x < ESPRI.pos1.x)
		xy.x = ESPRI.pos1.x;
	xy.y = (xy.x - ESPRI.pos1.x) * (ESPRI.pos2.y - ESPRI.pos1.y) /
	(ESPRI.pos2.x - ESPRI.pos1.x) + ESPRI.pos1.y;
	ESPRI.pos2.x = xy.x;
	ESPRI.pos2.y = xy.y;
}

void	barsanimate3(t_env *env, int i)
{
	if (ESPRI.pos1.y < ESPRI.pos2.y)
	{
		ESPRI.pos2.y = ESPRI.pos2.y - 0.4;
		if (ESPRI.pos1.y > ESPRI.pos2.y)
			ESPRI.pos2.y = ESPRI.pos1.y;
	}
	else
	{
		ESPRI.pos2.y = ESPRI.pos2.y + 0.4;
		if (ESPRI.pos1.y < ESPRI.pos2.y)
			ESPRI.pos2.y = ESPRI.pos1.y;
	}
}

void	barsanimate1(t_env *env, int i)
{
	if (ESPRI.pos1.x == ESPRI.pos2.x)
		barsanimate3(env, i);
	else if (ESPRI.pos1.y == ESPRI.pos2.y)
	{
		if (ESPRI.pos1.x < ESPRI.pos2.x)
		{
			ESPRI.pos2.x = ESPRI.pos2.x - 0.4;
			if (ESPRI.pos1.x > ESPRI.pos2.x)
				ESPRI.pos2.x = ESPRI.pos1.x;
		}
		else
		{
			ESPRI.pos2.x = ESPRI.pos2.x + 0.4;
			if (ESPRI.pos1.x < ESPRI.pos2.x)
				ESPRI.pos2.x = ESPRI.pos1.x;
		}
	}
	else
		barsanimate2(env, i);
}

void	barsanimate(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
		if (ESPRI.openbar == 1 && ESPRI.type == 2)
		{
			if (ESPRI.pos1.x != ESPRI.pos2.x || ESPRI.pos1.y != ESPRI.pos2.y)
				barsanimate1(env, i);
			else
			{
				ESPRI.visible = 0;
				ESPRI.openbar = 1;
			}
		}
}
