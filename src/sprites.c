/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:24:34 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 12:57:28 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	spriteplane2(t_env *env, t_rend *rend, int j, t_sprque *now)
{
	R->sprya = HWIN / 2 - (int)(YAW(R->sprceil, R->tspr.y) * R->spryscale);
	R->spryb = HWIN / 2 - (int)(YAW(R->sprfloor, R->tspr.y) * R->spryscale);
	R->sprbegx = MAX(R->sprx1, now->sx1);
	R->sprendx = MIN(R->sprx2, now->sx2);
	R->sprx = R->sprbegx;
	while (R->sprx < R->sprendx)
	{
		R->csprya = CLAMP(R->sprya, now->ytop[R->sprx], now->ybottom[R->sprx]);
		R->cspryb = CLAMP(R->spryb, now->ytop[R->sprx], now->ybottom[R->sprx]);
		R->txtx = (int)((double)(R->sprx - R->sprx1) /
					(double)(R->sprx2 - R->sprx1) * ESJT0->w);
		drawsprite(env, R, j);
		R->sprx++;
	}
}

void	spriteplane_support(t_env *env, t_rend *rend, int j)
{
	R->vspr.x = env->sprite[j].pos1.x - EPW.x;
	R->vspr.y = env->sprite[j].pos1.y - EPW.y;
	R->tspr.x = R->vspr.x * EPSIN - R->vspr.y * EPCOS;
	R->tspr1 = R->tspr.x + (double)(env->sprite[j].width) / 2.0;
	R->tspr2 = R->tspr.x - (double)(env->sprite[j].width) / 2.0;
	R->tspr.y = R->vspr.x * EPCOS + R->vspr.y * EPSIN;
}

void	spriteplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;

	now = R->sprq[env->sprite[j].sector];
	if (now.visible == 0)
		return ;
	R->nowsect = &(ESEC[now.sector]);
	spriteplane_support(env, rend, j);
	if (R->tspr.y <= 0)
		return ;
	R->sprxscale = WWIN * HFOV / R->tspr.y;
	R->spryscale = HWIN * VFOV / R->tspr.y;
	R->sprx1 = WWIN / 2 - (int)((R->tspr1) * R->sprxscale);
	R->sprx2 = WWIN / 2 - (int)((R->tspr2) * R->sprxscale);
	if (R->sprx1 > now.sx2 || R->sprx2 < now.sx1)
		return ;
	if (R->sprx1 + (R->sprx2 - R->sprx1) / 3 >= now.sx1 &&
		R->sprx2 - (R->sprx2 - R->sprx1) / 3 <= now.sx2)
		env->sprite[j].visible = 1;
	R->sprceil = R->nowsect->floor + env->sprite[j].height - EPW.z;
	R->sprfloor = R->nowsect->floor - EPW.z;
	spriteplane2(env, R, j, &now);
}

void	putspritesobjects(t_env *env, int i)
{
	if (ESPRI.spritedist <= 2 && ESPRI.type == 3 && env->player.hp < 100)
	{
		if (ESPRI.width > 0)
			env->player.hp = env->player.hp <= 70 ? env->player.hp += 30 : 100;
		ESPRI.width = 0;
	}
	if (ESPRI.spritedist <= 2 && ESPRI.type == 5)
	{
		if (ESPRI.width > 0)
		{
			Mix_PlayChannel(-1, env->sound[11], 0);
			env->player.keys++;
		}
		ESPRI.width = 0;
	}
	if (ESPRI.spritedist <= 2 && ESPRI.type == 6 && ESPRI.texnum == 0)
	{
		Mix_HaltMusic();
		Mix_PlayChannel(-1, env->sound[14], 0);
		env->state = 6;
	}
}

void	rendersprite(t_env *env, t_rend *rend)
{
	int	i;

	spritedist(env);
	sortsprite(env);
	barsanimate(env);
	i = -1;
	env->player.target = -1;
	while (++i < env->sprcount)
	{
		putspritesobjects(env, i);
		if (ESPRI.type != 2)
			spriteplane(env, R, i);
		else
			trplane(env, R, i);
	}
}
