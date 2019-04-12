/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritedist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:26:48 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 16:47:58 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	spritedist(t_env *env)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++i < env->sprcount)
	{
		if (env->sprite[i].type == 2)
		{
			x = (env->sprite[i].pos1.x + env->sprite[i].pos2.x) / 2;
			y = (env->sprite[i].pos1.y + env->sprite[i].pos2.y) / 2;
			env->sprite[i].spritedist = (env->player.where.x - x) *
			(env->player.where.x - x) + (env->player.where.y - y) *
			(env->player.where.y - y);
		}
		else
			env->sprite[i].spritedist = (env->player.where.x - env->sprite[i].pos1.x) *
			(env->player.where.x - env->sprite[i].pos1.x) + (env->player.where.y -
			env->sprite[i].pos1.y) * (env->player.where.y - env->sprite[i].pos1.y);
		env->sprite[i].visible = 0;
	}
}

void	drawtransp(t_env *env, t_rend *rend, int j)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += rend->ctrya * WWIN + rend->trx;
	y = rend->ctrya - 1;
	while (++y <= rend->ctryb)
	{
		txty = (int)((double)(y - rend->trya) / (double)(rend->tryb - rend->trya) * env->sprite[j].texture[0]->h);
		if (((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0)
			*pix = ((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx];
		pix += WWIN;
	}
}
