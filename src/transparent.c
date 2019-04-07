/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:26:23 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/07 18:29:36 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	drawtransp(t_env *env, t_rend *rend)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += rend->ctrya * WWIN + rend->trx;
	y = rend->ctrya - 1;
	//printf("!!!%d!!!\n", ((int *)(env->trton[j].texture->pixels))[0]);
	while (++y <= rend->ctryb)
	{
		txty = (int)((double)(y - rend->trya) / (double)(rend->tryb - rend->trya) * env->text[3]->h);
		if (((int *)(env->text[3]->pixels))[txty % env->text[3]->h * env->text[3]->w + rend->txtx] != -16777216 &&
		((int *)(env->text[3]->pixels))[txty % env->text[3]->h * env->text[3]->w + rend->txtx] != 0) 
			*pix = ((int *)(env->text[3]->pixels))[txty % env->text[3]->h * env->text[3]->w + rend->txtx];
		pix += WWIN;
	}
}

static void	trintersect(t_rend *rend, t_env *env)
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
			rend->org1 = (t_xy){rend->ttr1.x, rend->ttr1.y};
			rend->org2 = (t_xy){rend->ttr2.x, rend->ttr2.y};
			if (rend->ttr1.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->ttr1.x = rend->i1.x;
					rend->ttr1.y = rend->i1.y;
				}
				else 
				{
					rend->ttr1.x = rend->i2.x;
					rend->ttr1.y = rend->i2.y;
				}
			}
			if (rend->ttr2.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->ttr2.x = rend->i1.x;
					rend->ttr2.y = rend->i1.y;
				}
				else
				{
					rend->ttr2.x = rend->i2.x;
					rend->ttr2.y = rend->i2.y;
				}
			}
			if (fabs(rend->ttr2.x - rend->ttr1.x) > fabs(rend->ttr2.y - rend->ttr1.y))
			{
				rend->u0 = (rend->ttr1.x - rend->org1.x) * (env->text[0]->w - 1) / (rend->org2.x - rend->org1.x);
				rend->u1 = (rend->ttr2.x - rend->org1.x) * (env->text[0]->w - 1) / (rend->org2.x - rend->org1.x);
			}
			else
			{
				rend->u0 = (rend->ttr1.y - rend->org1.y) * (env->text[0]->w - 1) / (rend->org2.y - rend->org1.y);
				rend->u1 = (rend->ttr2.y - rend->org1.y) * (env->text[0]->w - 1) / (rend->org2.y - rend->org1.y);
			}
		}
}

void	trplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;
//	double a;

	now = rend->sprq[env->sprite[j].sector];
	if (now.visible == 0)
		return ;
	rend->nowsect = &(env->sector[now.sector]);
	rend->vtr1.x = env->sprite[j].pos1.x - env->player.where.x;
	rend->vtr1.y = env->sprite[j].pos1.y - env->player.where.y;
	rend->vtr2.x = env->sprite[j].pos2.x - env->player.where.x;
	rend->vtr2.y = env->sprite[j].pos2.y - env->player.where.y;
	rend->ttr1.x = rend->vtr1.x * env->player.sinang - rend->vtr1.y * env->player.cosang;
	rend->ttr1.y = rend->vtr1.x * env->player.cosang + rend->vtr1.y * env->player.sinang;
	rend->ttr2.x = rend->vtr2.x * env->player.sinang - rend->vtr2.y * env->player.cosang;
	rend->ttr2.y = rend->vtr2.x * env->player.cosang + rend->vtr2.y * env->player.sinang;
	//printf("%f %f\n", rend->ttr1.y, rend->ttr2.y);
	// if (rend->ttr1.x < rend->ttr2.x && rend->ttr1.y > rend->ttr2.y)
	// {
	// 	a = env->sprite[j].pos1.x;
	// 	env->sprite[j].pos1.x =env->sprite[j].pos2.x;
	// 	env->sprite[j].pos2.x = a;
	// 	a = env->sprite[j].pos1.y;
	// 	env->sprite[j].pos1.y =env->sprite[j].pos2.y;
	// 	env->sprite[j].pos2.y = a;
	// }
	if (rend->ttr1.y <= 0 && rend->ttr2.y  <= 0 )
		return ;
	trintersect(rend, env);
	rend->trxscale1 = WWIN * HFOV / rend->ttr1.y;
	rend->tryscale1 = HWIN * VFOV / rend->ttr1.y;
	rend->trx1 = WWIN / 2 - (int)((rend->ttr1.x) * rend->trxscale1);
	rend->trxscale2 = WWIN * HFOV / rend->ttr2.y;
	rend->tryscale2 = HWIN * VFOV / rend->ttr2.y;
	rend->trx2 = WWIN / 2 - (int)((rend->ttr2.x) * rend->trxscale2);
	if (rend->trx1 == rend->trx2 || rend->trx1 > now.sx2 || rend->trx2 < now.sx1)  ///// +1?
		return ;
	rend->trceil = env->sprite[j].height - env->player.where.z;
	rend->trfloor = env->sprite[j].floor - env->player.where.z;
	rend->try1a = HWIN / 2 - (int)(YAW(rend->trceil, rend->ttr1.y) * rend->tryscale1);
	rend->try1b = HWIN / 2 - (int)(YAW(rend->trfloor, rend->ttr1.y) * rend->tryscale1);
	rend->try2a = HWIN / 2 - (int)(YAW(rend->trceil, rend->ttr2.y) * rend->tryscale2);
	rend->try2b = HWIN / 2 - (int)(YAW(rend->trfloor, rend->ttr2.y) * rend->tryscale2);
	rend->trbegx = MAX(rend->trx1, now.sx1);
	rend->trendx = MIN(rend->trx2, now.sx2);
	rend->trx = rend->trbegx;
	rend->trya_int = (t_scaler)SCALER_INIT(rend->trx1, rend->trbegx, rend->trx2, rend->try1a, rend->try2a);
	rend->tryb_int = (t_scaler)SCALER_INIT(rend->trx1, rend->trbegx, rend->trx2, rend->try1b, rend->try2b);
	while (rend->trx < rend->trendx)
	{
		rend->trya = scaler_next(&rend->trya_int);
		rend->ctrya = CLAMP(rend->trya, now.ytop[rend->trx], now.ybottom[rend->trx]);
		rend->tryb = scaler_next(&rend->tryb_int);
		rend->ctryb = CLAMP(rend->tryb, now.ytop[rend->trx], now.ybottom[rend->trx]);
		//printf("%d %d\n", rend->trya, rend->tryb);
		rend->txtx = ((rend->u0 * ((rend->trx2 - rend->trx) * rend->ttr2.y) + rend->u1 * ((rend->trx - rend->trx1) * rend->ttr1.y))\
		/ ((rend->trx2 - rend->trx) * rend->ttr2.y + (rend->trx - rend->trx1) * rend->ttr1.y)) * (fabs(rend->vtr2.x - rend->vtr1.x) + fabs(rend->vtr2.y - rend->vtr1.y)) * 0.04;
		drawtransp(env, rend);
		rend->trx++;
	}
}