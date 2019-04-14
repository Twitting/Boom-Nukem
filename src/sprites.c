/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:24:34 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 16:32:57 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	drawsprite(t_env *env, t_rend *rend, int j)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += rend->csprya * WWIN + rend->sprx;
	y = rend->csprya - 1;
	while (++y <= rend->cspryb)
	{
		txty = (int)((double)(y - rend->sprya) / (double)(rend->spryb - rend->sprya) * env->sprite[j].texture[0]->h);
		if (y == HWIN / 2 && rend->sprx == WWIN / 2 && env->sprite[j].type == 1 &&
			((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0)
			env->player.target = j;
		if (((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx] != 0)
			*pix = ((int *)(env->sprite[j].texture[0]->pixels))[txty % env->sprite[j].texture[0]->h * env->sprite[j].texture[0]->w + rend->txtx];
		pix += WWIN;
	}
}

void	spriteplane2(t_env *env, t_rend *rend, int j, t_sprque *now)
{
	rend->sprya = HWIN / 2 - (int)(YAW(rend->sprceil, rend->tspr.y) * rend->spryscale);
	rend->spryb = HWIN / 2 - (int)(YAW(rend->sprfloor, rend->tspr.y) * rend->spryscale);
	rend->sprbegx = MAX(rend->sprx1, now->sx1);
	rend->sprendx = MIN(rend->sprx2, now->sx2);
	rend->sprx = rend->sprbegx;
	while (rend->sprx < rend->sprendx)
	{
		rend->csprya = CLAMP(rend->sprya, now->ytop[rend->sprx], now->ybottom[rend->sprx]);
		rend->cspryb = CLAMP(rend->spryb, now->ytop[rend->sprx], now->ybottom[rend->sprx]);
		rend->txtx = (int)((double)(rend->sprx - rend->sprx1) / (double)(rend->sprx2 - rend->sprx1) * env->sprite[j].texture[0]->w);
		drawsprite(env, rend, j);
		rend->sprx++;
	}
}

void	spriteplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;

	now = rend->sprq[env->sprite[j].sector];
	if (now.visible == 0)
		return ;
	rend->nowsect = &(env->sector[now.sector]);
	rend->vspr.x = env->sprite[j].pos1.x - env->player.where.x;
	rend->vspr.y = env->sprite[j].pos1.y - env->player.where.y;
	rend->tspr.x = rend->vspr.x * env->player.sinang - rend->vspr.y * env->player.cosang;
	rend->tspr1 = rend->tspr.x + (double)(env->sprite[j].width) / 2.0;
	rend->tspr2 = rend->tspr.x - (double)(env->sprite[j].width) / 2.0;
	rend->tspr.y = rend->vspr.x * env->player.cosang + rend->vspr.y * env->player.sinang;
	if (rend->tspr.y <= 0)
		return ;
	rend->sprxscale = WWIN * HFOV / rend->tspr.y;
	rend->spryscale = HWIN * VFOV / rend->tspr.y;
	rend->sprx1 = WWIN / 2 - (int)((rend->tspr1) * rend->sprxscale);
	rend->sprx2 = WWIN / 2 - (int)((rend->tspr2) * rend->sprxscale);
	if (rend->sprx1 > now.sx2 || rend->sprx2 < now.sx1)
		return ;
	if (rend->sprx1 + (rend->sprx2 - rend->sprx1) / 3 >= now.sx1 && rend->sprx2 - (rend->sprx2 - rend->sprx1) / 3 <= now.sx2)
		env->sprite[j].visible = 1;
	rend->sprceil = rend->nowsect->floor + env->sprite[j].height - env->player.where.z;
	rend->sprfloor = rend->nowsect->floor - env->player.where.z;
	spriteplane2(env, rend, j, &now);
}

void	putspritesobjects(t_env *env, int i)
{
	if (env->sprite[i].spritedist <= 2 && env->sprite[i].type == 3 && env->player.hp < 100)
	{
		if (env->sprite[i].width > 0)
		{
			if (env->player.hp <= 70)
				env->player.hp += 30;
			else
				env->player.hp = 100;
		}
		env->sprite[i].width = 0;
	}
	if (env->sprite[i].spritedist <= 2 && env->sprite[i].type == 5)
	{
		if (env->sprite[i].width > 0)
		{
			Mix_PlayChannel(-1, env->sound[11], 0);
			env->player.keys++;
		}
		env->sprite[i].width = 0;
	}
	if (env->sprite[i].spritedist <= 2 && env->sprite[i].type == 6 && env->sprite[i].texnum == 0)
		env->state = 6;
}

void	rendersprite(t_env *env, t_rend *rend)
{
	int	i;

	spritedist(env);
	sortsprite(env);
	i = -1;
	env->player.target = -1;
	while (++i < env->sprcount)
	{
		putspritesobjects(env, i);
		if (env->sprite[i].type != 2)
			spriteplane(env, rend, i);
		else
			trplane(env, rend, i);
	}
}
