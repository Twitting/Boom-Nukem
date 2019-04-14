/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:11:56 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 10:52:47 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	vline2(t_env *env, t_rend *rend, int y1, int y2, t_scaler ty)
{
	int *pix;
	int y;
	int txty;

	pix = (int*)env->surface->pixels;
	y1 = CLAMP(y1, 0, HWIN - 1) - 1;
	y2 = CLAMP(y2, 0, HWIN - 1) + 1;
	pix += y1 * WWIN + rend->x;
	y = y1;
	while (++y <= y2)
	{
		txty = scaler_next(&ty) * (rend->nowsect->ceiling - rend->nowsect->floor) / 64;
		*pix = ((int *)(rend->nowsect->text[1]->pixels))[txty % rend->nowsect->text[1]->h * rend->nowsect->text[1]->w + rend->txtx % rend->nowsect->text[1]->w];
		pix += WWIN;
	}
}

void	wallscale(t_env *env, t_rend *rend)
{
	if (rend->t1.y <= 0.5)
	{
		rend->t1.x = (0.5 - rend->t1.y) * (rend->t2.x - rend->t1.x) / (rend->t2.y - rend->t1.y) + rend->t1.x;
		rend->t1.y = 0.5;
	}
	rend->xscale1 = WWIN * HFOV / rend->t1.y;
	rend->yscale1 = HWIN * VFOV / rend->t1.y;
	rend->x1 = WWIN / 2 + (int)(-rend->t1.x * rend->xscale1);
	rend->xscale2 = WWIN * HFOV / rend->t2.y;
	rend->yscale2 = HWIN * VFOV / rend->t2.y;
	rend->x2 = WWIN / 2 + (int)(-rend->t2.x * rend->xscale2);
	rend->yceil = rend->nowsect->ceiling - env->player.where.z;
	rend->yfloor = rend->nowsect->floor - env->player.where.z;
	if (rend->nowsect->neighbors[rend->s] >= 0)
	{
		rend->nyceil = env->sector[rend->nowsect->neighbors[rend->s]].ceiling - env->player.where.z;
		rend->nyfloor = env->sector[rend->nowsect->neighbors[rend->s]].floor - env->player.where.z;
	}
}

void	textceilfloor(t_env *env, t_rend *rend)
{
	if (rend->y >= rend->cyb)
	{
		rend->hei = rend->y < rend->cya ? rend->yceil : rend->yfloor;
		TOMAPCCORD(rend->hei, rend->x, rend->y, rend->mapx, rend->mapz);
		rend->txtx = rend->mapx * rend->nowsect->text[0]->w / 12;
		rend->txtz = rend->mapz * rend->nowsect->text[0]->w / 12;
		rend->pel = ((int*)rend->nowsect->text[0]->pixels)[abs(rend->txtz) % rend->nowsect->text[0]->h * rend->nowsect->text[0]->w + abs(rend->txtx) % rend->nowsect->text[0]->w];
	}
	if (rend->y < rend->cya)
	{
		if (rend->nowsect->sky != 1)
		{
			rend->hei = rend->y < rend->cya ? rend->yceil : rend->yfloor;
			TOMAPCCORD(rend->hei, rend->x, rend->y, rend->mapx, rend->mapz);
			rend->txtx = rend->mapx * rend->nowsect->text[2]->w / 12; // почему 256??
			rend->txtz = rend->mapz * rend->nowsect->text[2]->w / 12;
			rend->pel = ((int*)rend->nowsect->text[2]->pixels)[abs(rend->txtz) % rend->nowsect->text[2]->h * rend->nowsect->text[2]->w + abs(rend->txtx) % rend->nowsect->text[2]->w];
		}
		else
			rend->pel = ((int *)(env->text[2]->pixels))[(int)(rend->y + 100 * (env->player.yaw + 3)) % env->text[2]->h * env->text[2]->w + (int)(env->player.angle / 6.2 * env->text[2]->w + rend->x) % env->text[2]->w];
	}
	((int*)env->surface->pixels)[rend->y * WWIN + rend->x] = rend->pel;
}

void	rendportals(t_env *env, t_rend *rend)
{
	rend->nya = (rend->x - rend->x1) * (rend->ny2a - rend->ny1a) / (rend->x2 - rend->x1) + rend->ny1a;
	rend->ncya = CLAMP(rend->nya, rend->ytop[rend->x], rend->ybottom[rend->x]);
	rend->nyb = (rend->x - rend->x1) * (rend->ny2b - rend->ny1b) / (rend->x2 - rend->x1) + rend->ny1b;
	rend->ncyb = CLAMP(rend->nyb, rend->ytop[rend->x], rend->ybottom[rend->x]);
	vline2(env, rend, rend->cya, rend->ncya - 1, (t_scaler)SCALER_INIT(rend->ya, rend->cya, rend->yb, 0, (env->text[0]->w - 1)));
	if (rend->nowsect->sky != 1)
	{
		if (env->sector[rend->nowsect->neighbors[rend->s]].sky == 1)
			rend->ytop[rend->x] = CLAMP(rend->cya + 1, rend->ytop[rend->x], HWIN - 1);
		else
			rend->ytop[rend->x] = CLAMP(MAX(rend->cya, rend->ncya), rend->ytop[rend->x], HWIN - 1);
	}
	else
	{
		if (env->sector[rend->nowsect->neighbors[rend->s]].sky == 1)
			rend->ytop[rend->x] = CLAMP(MIN(rend->cya, rend->ncya), rend->ytop[rend->x], HWIN - 1);
		else
			rend->ytop[rend->x] = CLAMP(rend->ncya, rend->ytop[rend->x], HWIN - 1);
	}
	vline2(env, rend, rend->ncyb + 1, rend->cyb, (t_scaler)SCALER_INIT(rend->ya, rend->ncyb + 1, rend->yb, 0, (env->text[0]->w - 1)));
	rend->ybottom[rend->x] = CLAMP(MIN(rend->cyb, rend->ncyb), 0, rend->ybottom[rend->x]);
}

void	wallxloop(t_env *env, t_rend *rend)
{
	while (rend->x <= rend->endx)
	{
		rend->ya = scaler_next(&rend->ya_int);
		rend->cya = CLAMP(rend->ya, rend->ytop[rend->x], rend->ybottom[rend->x]);
		rend->yb = scaler_next(&rend->yb_int);
		rend->cyb = CLAMP(rend->yb, rend->ytop[rend->x], rend->ybottom[rend->x]);
		rend->y = rend->ytop[rend->x] - 2;
		while (++rend->y <= rend->ybottom[rend->x])
		{
			if (rend->y >= rend->cya && rend->y <= rend->cyb)
			{
				rend->y = rend->cyb;
				continue;
			}
			textceilfloor(env, rend);
		}
		rend->txtx = ((rend->u0 * ((rend->x2 - rend->x) * rend->t2.y) + rend->u1 * ((rend->x - rend->x1) * rend->t1.y))\
		/ ((rend->x2 - rend->x) * rend->t2.y + (rend->x - rend->x1) * rend->t1.y)) * (fabs(rend->vx2 - rend->vx1) + fabs(rend->vy2 - rend->vy1)) * 0.04;
		if (rend->nowsect->neighbors[rend->s] >= 0)
			rendportals(env, rend);
		else
			vline2(env, rend, rend->cya, rend->cyb, (t_scaler)SCALER_INIT(rend->ya, rend->cya, rend->yb, 0, (env->text[0]->w - 1)));
		rend->x++;
	}
}
