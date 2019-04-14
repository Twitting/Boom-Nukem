/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openbars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:30:58 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 16:01:06 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	openbars(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->sprcount)
		if (env->sprite[i].openbar == 0 && env->sprite[i].type == 2 &&
		env->sprite[i].sector == (int)env->player.sector)
			if (env->sprite[i].spritedist <= 10)
			{
				env->sprite[i].openbar = 1;
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

	xy.x = env->sprite[i].pos2.x - 0.3;
	if (xy.x < env->sprite[i].pos1.x)
		xy.x = env->sprite[i].pos1.x;
	xy.y = (xy.x - env->sprite[i].pos1.x) *	(env->sprite[i].pos2.y - env->sprite[i].pos1.y) /
	(env->sprite[i].pos2.x - env->sprite[i].pos1.x) + env->sprite[i].pos1.y;
	env->sprite[i].pos2.x = xy.x;
	env->sprite[i].pos2.y = xy.y;
}

void	barsanimate1(t_env *env, int i)
{
	//ft_putendl("open!");
	if (env->sprite[i].pos1.x == env->sprite[i].pos2.x)
	{
		if (env->sprite[i].pos1.y < env->sprite[i].pos2.y)
		{
			env->sprite[i].pos2.y = env->sprite[i].pos2.y - 0.4;
			if (env->sprite[i].pos1.y > env->sprite[i].pos2.y)
				env->sprite[i].pos2.y = env->sprite[i].pos1.y;
		}
		else
		{
			env->sprite[i].pos2.y = env->sprite[i].pos2.y + 0.4;
			if (env->sprite[i].pos1.y < env->sprite[i].pos2.y)
				env->sprite[i].pos2.y = env->sprite[i].pos1.y;
		}
	}
	else if (env->sprite[i].pos1.y == env->sprite[i].pos2.y)
	{
		if (env->sprite[i].pos1.x < env->sprite[i].pos2.x)
		{
			env->sprite[i].pos2.x = env->sprite[i].pos2.x - 0.4;
			if (env->sprite[i].pos1.x > env->sprite[i].pos2.x)
				env->sprite[i].pos2.x = env->sprite[i].pos1.x;
		}
		else
		{
			env->sprite[i].pos2.x = env->sprite[i].pos2.x + 0.4;
			if (env->sprite[i].pos1.x < env->sprite[i].pos2.x)
				env->sprite[i].pos2.x = env->sprite[i].pos1.x;
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
		if (env->sprite[i].openbar == 1 && env->sprite[i].type == 2)
		{
			if (env->sprite[i].pos1.x != env->sprite[i].pos2.x || env->sprite[i].pos1.y != env->sprite[i].pos2.y)
				barsanimate1(env, i);
			else
			{
				env->sprite[i].visible = 0;
				env->sprite[i].openbar = 1;
			}	
		}
}
