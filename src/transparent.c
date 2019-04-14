/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:26:23 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 19:20:32 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	trintersect2(t_rend *rend, t_env *env, int j)
{
	if (rend->ttr1.y < rend->nfz.x)
	{
		if (rend->i1.y > 0)
			rend->ttr1 = rend->i1;
		else
			rend->ttr1 = rend->i2;
	}
	if (rend->ttr2.y < rend->nfz.x)
	{
		if (rend->i1.y > 0)
			rend->ttr2 = rend->i1;
		else
			rend->ttr2 = rend->i2;
	}
	if (fabs(rend->ttr2.x - rend->ttr1.x) > fabs(rend->ttr2.y - rend->ttr1.y))
	{
		rend->u0 = (rend->ttr1.x - RO1.x) * (ESJT0->w - 1) / (RO2.x - RO1.x);
		rend->u1 = (rend->ttr2.x - RO1.x) * (ESJT0->w - 1) / (RO2.x - RO1.x);
	}
	else
	{
		rend->u0 = (rend->ttr1.y - RO1.y) * (ESJT0->w - 1) / (RO2.y - RO1.y);
		rend->u1 = (rend->ttr2.y - RO1.y) * (ESJT0->w - 1) / (RO2.y - RO1.y);
	}
}

void	trintersect(t_rend *rend, t_env *env, int j)
{
	if (rend->ttr1.y <= 0 || rend->ttr2.y <= 0)
	{
		rend->nfz.x = 1e-4;
		rend->nfz.y = 5;
		rend->nfside.x = 1e-5;
		rend->nfside.y = 20;
		rend->wintsect1.x = -rend->nfside.x;
		rend->wintsect1.y = rend->nfz.x;
		rend->wintsect2.x = -rend->nfside.y;
		rend->wintsect2.y = rend->nfz.y;
		rend->i1 = intersect(rend->ttr1, rend->ttr2, rend->wintsect1, rend->wintsect2);
		rend->wintsect1.x = rend->nfside.x;
		rend->wintsect2.x = rend->nfside.y;
		rend->i2 = intersect(rend->ttr1, rend->ttr2, rend->wintsect1, rend->wintsect2);
		RO1 = (t_xy){rend->ttr1.x, rend->ttr1.y};
		RO2 = (t_xy){rend->ttr2.x, rend->ttr2.y};
		trintersect2(rend, env, j);
	}
}

void	trscale(t_rend *rend)
{
	if (rend->ttr1.y <= 0.5)
	{
		rend->ttr1.x = (0.5 - rend->ttr1.y) * (rend->ttr2.x - rend->ttr1.x) / (rend->ttr2.y - rend->ttr1.y) + rend->ttr1.x;
		rend->ttr1.y = 0.5;
	}
	rend->trxscale1 = WWIN * HFOV / rend->ttr1.y;
	rend->tryscale1 = HWIN * VFOV / rend->ttr1.y;
	rend->trx1 = WWIN / 2 - (int)((rend->ttr1.x) * rend->trxscale1);
	rend->trxscale2 = WWIN * HFOV / rend->ttr2.y;
	rend->tryscale2 = HWIN * VFOV / rend->ttr2.y;
	rend->trx2 = WWIN / 2 - (int)((rend->ttr2.x) * rend->trxscale2);
}

t_scaler	scaler_init_support3(t_rend *rend)
{
	t_scaler temp;
	temp = (t_scaler)
	{rend->try1a + (rend->trbegx - 1 - rend->trx1) *
		(rend->try2a - rend->try1a) / (rend->trx2 - rend->trx1),
		((rend->try2a < rend->try1a) ^
		(rend->trx2 < rend->trx1)) ? -1 : 1,
		abs(rend->try2a - rend->try1a),
		abs(rend->trx2 - rend->trx1),
		(int)((rend->trbegx - 1 - rend->trx1) * abs(rend->try2a -
		rend->try1a)) % abs(rend->trx2 - rend->trx1)};
	return (temp);
}

t_scaler	scaler_init_support4(t_rend *rend)
{
	t_scaler temp;

	temp = (t_scaler)
	{rend->try1b + (rend->trbegx - 1 - rend->trx1) *
		(rend->try2b - rend->try1b) / (rend->trx2 - rend->trx1),
		((rend->try2b < rend->try1b) ^
		(rend->trx2 < rend->trx1)) ? -1 : 1,
		abs(rend->try2b - rend->try1b),
		abs(rend->trx2 - rend->trx1),
		(int)((rend->trbegx - 1 - rend->trx1) * abs(rend->try2b -
		rend->try1b)) % abs(rend->trx2 - rend->trx1)};
	return (temp);
}

void	trstart(t_rend *rend, t_env *env, int j, t_sprque *now)
{
	rend->trceil = env->sprite[j].height - EPW.z;
	rend->trfloor = env->sprite[j].floor - EPW.z;
	rend->try1a = HWIN / 2 - (int)(YAW(rend->trceil, rend->ttr1.y) * rend->tryscale1);
	rend->try1b = HWIN / 2 - (int)(YAW(rend->trfloor, rend->ttr1.y) * rend->tryscale1);
	rend->try2a = HWIN / 2 - (int)(YAW(rend->trceil, rend->ttr2.y) * rend->tryscale2);
	rend->try2b = HWIN / 2 - (int)(YAW(rend->trfloor, rend->ttr2.y) * rend->tryscale2);
	rend->trbegx = MAX(rend->trx1, now->sx1);
	rend->trendx = MIN(rend->trx2, now->sx2);
	rend->trx = rend->trbegx;
	rend->trya_int = scaler_init_support3(rend);
	rend->tryb_int = scaler_init_support4(rend);;
	while (rend->trx < rend->trendx)
	{
		rend->trya = scaler_next(&rend->trya_int);
		rend->ctrya = CLAMP(rend->trya, now->ytop[rend->trx], now->ybottom[rend->trx]);
		rend->tryb = scaler_next(&rend->tryb_int);
		rend->ctryb = CLAMP(rend->tryb, now->ytop[rend->trx], now->ybottom[rend->trx]);
		rend->txtx = ((rend->u0 * ((rend->trx2 - rend->trx) * rend->ttr2.y) + rend->u1 * ((rend->trx - rend->trx1) * rend->ttr1.y))
		/ ((rend->trx2 - rend->trx) * rend->ttr2.y + (rend->trx - rend->trx1) * rend->ttr1.y)) * (fabs(rend->vtr2.x - rend->vtr1.x) + fabs(rend->vtr2.y - rend->vtr1.y)) * 0.002;
		drawtransp(env, rend, j);
		rend->trx++;
	}
}

void	trplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;

	now = rend->sprq[env->sprite[j].sector];
	if (now.visible == 0 || env->sprite[j].visible == 0)
		return ;
	rend->nowsect = &(ESEC[now.sector]);
	rend->vtr1.x = env->sprite[j].pos1.x - EPW.x;
	rend->vtr1.y = env->sprite[j].pos1.y - EPW.y;
	rend->vtr2.x = env->sprite[j].pos2.x - EPW.x;
	rend->vtr2.y = env->sprite[j].pos2.y - EPW.y;
	rend->ttr1.x = rend->vtr1.x * EPSIN - rend->vtr1.y * EPCOS;
	rend->ttr1.y = rend->vtr1.x * EPCOS + rend->vtr1.y * EPSIN;
	rend->ttr2.x = rend->vtr2.x * EPSIN - rend->vtr2.y * EPCOS;
	rend->ttr2.y = rend->vtr2.x * EPCOS + rend->vtr2.y * EPSIN;
	if (rend->ttr1.y <= 0 && rend->ttr2.y <= 0)
		return ;
	rend->u0 = 0;
	rend->u1 = ESJT0->w;
	trintersect(rend, env, j);
	trscale(rend);
	if (rend->trx1 >= rend->trx2 || rend->trx1 > now.sx2 || rend->trx2 < now.sx1)
		return ;
	trstart(rend, env, j, &now);
}
