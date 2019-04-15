/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:11:56 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 16:22:31 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void		wallscale(t_env *env, t_rend *rend)
{
	if (R->t1.y <= 0.5)
	{
		R->t1.x = (0.5 - R->t1.y) * (R->t2.x - R->t1.x)
			/ (R->t2.y - R->t1.y) + R->t1.x;
		R->t1.y = 0.5;
	}
	if (R->t2.y <= 0.5)
	{
		R->t2.x = (0.5 - R->t2.y) * (R->t1.x - R->t2.x)
		/ (R->t1.y - R->t2.y) + R->t2.x;
		R->t2.y = 0.5;
	}
	R->xscale1 = WWIN * HFOV / R->t1.y;
	R->yscale1 = HWIN * VFOV / R->t1.y;
	R->x1 = WWIN / 2 + (int)(-R->t1.x * R->xscale1);
	R->xscale2 = WWIN * HFOV / R->t2.y;
	R->yscale2 = HWIN * VFOV / R->t2.y;
	R->x2 = WWIN / 2 + (int)(-R->t2.x * R->xscale2);
	R->yceil = R->nowsect->ceiling - EPW.z;
	R->yfloor = R->nowsect->floor - EPW.z;
	if (R->nowsect->neighbors[R->s] >= 0)
	{
		R->nyceil = ESEC[R->nowsect->neighbors[R->s]].ceiling - EPW.z;
		R->nyfloor = ESEC[R->nowsect->neighbors[R->s]].floor - EPW.z;
	}
}

void		tomapccord(t_rend *rend, t_env *env)
{
	double rtx;
	double rtz;

	R->mapz = (R->hei) * HWIN * VFOV / ((HWIN / 2
		- (R->y)) - env->player.yaw * HWIN * VFOV);
	R->mapx = (R->mapz) * (WWIN / 2 - (R->x)) / (WWIN * HFOV);
	rtx = (R->mapz) * EPCOS + (R->mapx) * EPSIN;
	rtz = (R->mapz) * EPSIN - (R->mapx) * EPCOS;
	R->mapx = rtx + EPW.x;
	R->mapz = rtz + EPW.y;
}

void		textceilfloor_support(t_env *env, t_rend *rend)
{
	R->hei = R->y < R->cya ? R->yceil : R->yfloor;
	tomapccord(R, env);
	R->txtx = R->mapx * R->NST[0]->w / 12;
	R->txtz = R->mapz * R->NST[0]->w / 12;
	R->pel = ((int*)R->NST[0]->pixels)[abs(R->txtz) %
	R->NST[0]->h * R->NST[0]->w + abs(R->txtx) % R->NST[0]->w];
}

void		textceilfloor(t_env *env, t_rend *rend)
{
	if (R->y >= R->cyb)
	{
		textceilfloor_support(env, rend);
	}
	if (R->y < R->cya)
	{
		if (R->nowsect->sky != 1)
		{
			R->hei = R->y < R->cya ? R->yceil : R->yfloor;
			tomapccord(R, env);
			R->txtx = R->mapx * R->NST[2]->w / 12;
			R->txtz = R->mapz * R->NST[2]->w / 12;
			R->pel = ((int*)R->NST[2]->pixels)[abs(R->txtz) %
			R->NST[2]->h * R->NST[2]->w + abs(R->txtx) % R->NST[2]->w];
		}
		else
			R->pel = ((int *)(ET[2]->pixels))[(int)(R->y + 100 *
			(env->player.yaw + 3)) % ET[2]->h * ET[2]->w +
			(int)(PANG / 6.2 * ET[2]->w + R->x) % ET[2]->w];
	}
	((int*)env->surface->pixels)[R->y * WWIN + R->x] = R->pel;
}

void		wallxloop(t_env *env, t_rend *rend)
{
	while (R->x++ <= R->endx)
	{
		R->ya = scaler_next(&R->ya_int);
		R->cya = CLAMP(R->ya, R->ytop[R->x], R->ybottom[R->x]);
		R->yb = scaler_next(&R->yb_int);
		R->cyb = CLAMP(R->yb, R->ytop[R->x], R->ybottom[R->x]);
		R->y = R->ytop[R->x] - 2;
		while (++R->y <= R->ybottom[R->x])
		{
			if (R->y >= R->cya && R->y <= R->cyb)
			{
				R->y = R->cyb;
				continue;
			}
			textceilfloor(env, R);
		}
		R->txtx = ((R->u0 * ((R->x2 - R->x) * R->t2.y)
			+ R->u1 * ((R->x - R->x1) * R->t1.y))\
		/ ((R->x2 - R->x) * R->t2.y + (R->x - R->x1) * R->t1.y))
		* (fabs(R->vx2 - R->vx1) + fabs(R->vy2 - R->vy1)) * 0.04;
		if (R->nowsect->neighbors[R->s] >= 0)
			rendportals(env, R);
		else
			vlinewall(env, R);
	}
}
