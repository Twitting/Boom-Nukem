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

void	trintersect2(t_rend *R, t_env *env, int j)
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

void	trintersect(t_rend *R, t_env *env, int j)
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

void	trscale(t_rend *R)
{
	if (R->ttr1.y <= 0.5)
	{
		R->ttr1.x = (0.5 - R->ttr1.y) * (R->ttr2.x - R->ttr1.x) / (R->ttr2.y - R->ttr1.y) + R->ttr1.x;
		R->ttr1.y = 0.5;
	}
	R->trxscale1 = WWIN * HFOV / R->ttr1.y;
	R->tryscale1 = HWIN * VFOV / R->ttr1.y;
	R->trx1 = WWIN / 2 - (int)((R->ttr1.x) * R->trxscale1);
	R->trxscale2 = WWIN * HFOV / R->ttr2.y;
	R->tryscale2 = HWIN * VFOV / R->ttr2.y;
	R->trx2 = WWIN / 2 - (int)((R->ttr2.x) * R->trxscale2);
}

t_scaler	scaler_init_support3(t_rend *R)
{
	t_scaler temp;
	temp = (t_scaler)
	{R->try1a + (R->trbegx - 1 - R->trx1) *
		(R->try2a - R->try1a) / (R->trx2 - R->trx1),
		((R->try2a < R->try1a) ^
		(R->trx2 < R->trx1)) ? -1 : 1,
		abs(R->try2a - R->try1a),
		abs(R->trx2 - R->trx1),
		(int)((R->trbegx - 1 - R->trx1) * abs(R->try2a -
		R->try1a)) % abs(R->trx2 - R->trx1)};
	return (temp);
}

t_scaler	scaler_init_support4(t_rend *R)
{
	t_scaler temp;

	temp = (t_scaler)
	{R->try1b + (R->trbegx - 1 - R->trx1) *
		(R->try2b - R->try1b) / (R->trx2 - R->trx1),
		((R->try2b < R->try1b) ^
		(R->trx2 < R->trx1)) ? -1 : 1,
		abs(R->try2b - R->try1b),
		abs(R->trx2 - R->trx1),
		(int)((R->trbegx - 1 - R->trx1) * abs(R->try2b -
		R->try1b)) % abs(R->trx2 - R->trx1)};
	return (temp);
}

void	trstart(t_rend *R, t_env *env, int j, t_sprque *now)
{
	R->trceil = env->sprite[j].height - EPW.z;
	R->trfloor = env->sprite[j].floor - EPW.z;
	R->try1a = HWIN / 2 - (int)(YAW(R->trceil, R->ttr1.y) * R->tryscale1);
	R->try1b = HWIN / 2 - (int)(YAW(R->trfloor, R->ttr1.y) * R->tryscale1);
	R->try2a = HWIN / 2 - (int)(YAW(R->trceil, R->ttr2.y) * R->tryscale2);
	R->try2b = HWIN / 2 - (int)(YAW(R->trfloor, R->ttr2.y) * R->tryscale2);
	R->trbegx = MAX(R->trx1, now->sx1);
	R->trendx = MIN(R->trx2, now->sx2);
	R->trx = R->trbegx;
	R->trya_int = scaler_init_support3(R);
	R->tryb_int = scaler_init_support4(R);;
	while (R->trx < R->trendx)
	{
		R->trya = scaler_next(&R->trya_int);
		R->ctrya = CLAMP(R->trya, now->ytop[R->trx], now->ybottom[R->trx]);
		R->tryb = scaler_next(&R->tryb_int);
		R->ctryb = CLAMP(R->tryb, now->ytop[R->trx], now->ybottom[R->trx]);
		R->txtx = ((R->u0 * ((R->trx2 - R->trx) * R->ttr2.y) + R->u1 * ((R->trx - R->trx1) * R->ttr1.y))
		/ ((R->trx2 - R->trx) * R->ttr2.y + (R->trx - R->trx1) * R->ttr1.y)) * (fabs(R->vtr2.x - R->vtr1.x) + fabs(R->vtr2.y - R->vtr1.y)) * 0.002;
		drawtransp(env, R, j);
		R->trx++;
	}
}

void	trplane(t_env *env, t_rend *R, int j)
{
	t_sprque		now;

	now = R->sprq[env->sprite[j].sector];
	if (now.visible == 0 || env->sprite[j].visible == 0)
		return ;
	R->nowsect = &(ESEC[now.sector]);
	R->vtr1.x = env->sprite[j].pos1.x - EPW.x;
	R->vtr1.y = env->sprite[j].pos1.y - EPW.y;
	R->vtr2.x = env->sprite[j].pos2.x - EPW.x;
	R->vtr2.y = env->sprite[j].pos2.y - EPW.y;
	R->ttr1.x = R->vtr1.x * EPSIN - R->vtr1.y * EPCOS;
	R->ttr1.y = R->vtr1.x * EPCOS + R->vtr1.y * EPSIN;
	R->ttr2.x = R->vtr2.x * EPSIN - R->vtr2.y * EPCOS;
	R->ttr2.y = R->vtr2.x * EPCOS + R->vtr2.y * EPSIN;
	if (R->ttr1.y <= 0 && R->ttr2.y <= 0)
		return ;
	R->u0 = 0;
	R->u1 = ESJT0->w;
	trintersect(R, env, j);
	trscale(R);
	if (R->trx1 >= R->trx2 || R->trx1 > now.sx2 || R->trx2 < now.sx1)
		return ;
	trstart(R, env, j, &now);
}
