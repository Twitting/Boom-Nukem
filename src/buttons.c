/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:47:12 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/07 19:11:53 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void	drawbutton(t_env *env, t_rend *rend)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += rend->cbutya * WWIN + rend->butx;
	y = rend->cbutya - 1;
	//printf("!!!%d!!!\n", ((int *)(env->button[j].texture->pixels))[0]);
	while (++y <= rend->cbutyb)
	{
		txty = (int)((double)(y - rend->butya) / (double)(rend->butyb - rend->butya) * env->text[1]->h);
		if (((int *)(env->text[1]->pixels))[txty % env->text[1]->h * env->text[1]->w + rend->txtx] != -16777216)
			*pix = ((int *)(env->text[1]->pixels))[txty % env->text[1]->h * env->text[1]->w + rend->txtx];
		pix += WWIN;
	}
}

static void	butintersect(t_rend *rend)
{
	if (rend->tbut1.y <= 0 || rend->tbut2.y <= 0)
		{
			rend->nfz.x = 1e-4;
			rend->nfz.y = 5;
			rend->nfside.x = 1e-5;
			rend->nfside.y = 20;
			rend->wintsect1.x = -rend->nfside.x;
			rend->wintsect1.y = rend->nfz.x;
			rend->wintsect2.x = -rend->nfside.y;
			rend->wintsect2.y = rend->nfz.y;
			rend->i1 = intersect(rend->tbut1, rend->tbut2, rend->wintsect1, rend->wintsect2);
			rend->wintsect1.x = rend->nfside.x;
			rend->wintsect2.x = rend->nfside.y;
			rend->i2 = intersect(rend->tbut1, rend->tbut2, rend->wintsect1, rend->wintsect2);
			rend->org1 = (t_xy){rend->tbut1.x, rend->tbut1.y};
			rend->org2 = (t_xy){rend->tbut2.x, rend->tbut2.y};
			if (rend->tbut1.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->tbut1.x = rend->i1.x;
					rend->tbut1.y = rend->i1.y;
				}
				else 
				{
					rend->tbut1.x = rend->i2.x;
					rend->tbut1.y = rend->i2.y;
				}
			}
			if (rend->tbut2.y < rend->nfz.x)
			{
				if (rend->i1.y > 0)
				{
					rend->tbut2.x = rend->i1.x;
					rend->tbut2.y = rend->i1.y;
				}
				else
				{
					rend->tbut2.x = rend->i2.x;
					rend->tbut2.y = rend->i2.y;
				}
			}
		}
}

void	butplane(t_env *env, t_rend *rend, int j)
{
	t_sprque		now;

	now = rend->sprq[j];
	if (now.visible == 0)
		return ;
	rend->nowsect = &(env->sector[now.sector]);
	rend->vbut1.x = env->button[j].x1 - env->player.where.x;
	rend->vbut1.y = env->button[j].y1 - env->player.where.y;
	rend->vbut2.x = env->button[j].x2 - env->player.where.x;
	rend->vbut2.y = env->button[j].y2 - env->player.where.y;
	rend->tbut1.x = rend->vbut1.x * env->player.sinang - rend->vbut1.y * env->player.cosang;
	rend->tbut1.y = rend->vbut1.x * env->player.cosang + rend->vbut1.y * env->player.sinang;
	rend->tbut2.x = rend->vbut2.x * env->player.sinang - rend->vbut2.y * env->player.cosang;
	rend->tbut2.y = rend->vbut2.x * env->player.cosang + rend->vbut2.y * env->player.sinang;
	if (rend->tbut1.y <= 0 && rend->tbut2.y <= 0)
		return ;
	butintersect(rend);
	if (rend->tbut1.y <= 0.5)
	{
		rend->tbut1.x = (0.5 - rend->tbut1.y) * (rend->tbut2.x - rend->tbut1.x) / (rend->tbut2.y - rend->tbut1.y) + rend->tbut1.x;
		rend->tbut1.y = 0.5;
	}
	rend->butxscale1 = WWIN * HFOV / rend->tbut1.y;
	rend->butyscale1 = HWIN * VFOV / rend->tbut1.y;
	rend->butx1 = WWIN / 2 - (int)((rend->tbut1.x) * rend->butxscale1);
	rend->butxscale2 = WWIN * HFOV / rend->tbut2.y;
	rend->butyscale2 = HWIN * VFOV / rend->tbut2.y;
	rend->butx2 = WWIN / 2 - (int)((rend->tbut2.x) * rend->butxscale2);
	if (rend->butx1 == rend->butx2 || rend->butx1 > now.sx2 || rend->butx2 < now.sx1)  ///// +1?
		return ;
	rend->butceil =  rend->nowsect->floor + 5 + BUTTONHEIGHT - env->player.where.z;
	rend->butfloor = rend->nowsect->floor + 5 - env->player.where.z;
	rend->buty1a = HWIN / 2 - (int)(YAW(rend->butceil, rend->tbut1.y) * rend->butyscale1);
	rend->buty1b = HWIN / 2 - (int)(YAW(rend->butfloor, rend->tbut1.y) * rend->butyscale1);
	rend->buty2a = HWIN / 2 - (int)(YAW(rend->butceil, rend->tbut2.y) * rend->butyscale2);
	rend->buty2b = HWIN / 2 - (int)(YAW(rend->butfloor, rend->tbut2.y) * rend->butyscale2);
	rend->butbegx = MAX(rend->butx1, now.sx1);
	rend->butendx = MIN(rend->butx2, now.sx2);
	rend->butx = rend->butbegx;
	rend->butya_int = (t_scaler)SCALER_INIT(rend->butx1, rend->butbegx, rend->butx2, rend->buty1a, rend->buty2a);
	rend->butyb_int = (t_scaler)SCALER_INIT(rend->butx1, rend->butbegx, rend->butx2, rend->buty1b, rend->buty2b);
	while (rend->butx < rend->butendx)
	{
		rend->butya = scaler_next(&rend->butya_int);
		rend->cbutya = CLAMP(rend->butya, now.ytop[rend->butx], now.ybottom[rend->butx]);
		rend->butyb = scaler_next(&rend->butyb_int);
		rend->cbutyb = CLAMP(rend->butyb, now.ytop[rend->butx], now.ybottom[rend->butx]);
		//printf("%d %d\n", rend->butya, rend->butyb);
		rend->txtx = (int)((double)(rend->butx - rend->butx1) / (double)(rend->butx2 - rend->butx1) * env->text[1]->w);
		drawbutton(env, rend);
		rend->butx++;
	}
}

void	renderbutton(t_env *env, t_rend *rend)
{
	int	i;

	i = -1;
	while (++i < (int)env->nsectors)
	{
		butplane(env, rend, i);
	}
}
