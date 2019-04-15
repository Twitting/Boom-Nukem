/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:47:12 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 12:18:44 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

void		drawbutton(t_env *env, t_rend *rend)
{
	int y;
	int *pix;
	int txty;

	pix = (int *)env->surface->pixels;
	pix += R->cbutya * WWIN + R->butx;
	y = R->cbutya - 1;
	while (++y <= R->cbutyb)
	{
		txty = (int)((double)(y - R->butya) /
				(double)(R->butyb - R->butya) * ET[1]->h);
		if (((int *)(ET[1]->pixels))[txty % ET[1]->h
				* ET[1]->w + R->txtx] != -16777216)
			*pix = ((int *)(ET[1]->pixels))[txty % ET[1]->h
					* ET[1]->w + R->txtx];
		pix += WWIN;
	}
}

static void	butintersect_support(t_rend *rend, t_env *env)
{
	if (R->tbut1.y < R->nfz.x)
	{
		if (R->i1.y > 0)
			R->tbut1 = R->i1;
		else
			R->tbut1 = R->i2;
	}
	if (R->tbut2.y < R->nfz.x)
	{
		if (R->i1.y > 0)
			R->tbut2 = R->i1;
		else
			R->tbut2 = R->i2;
	}
	if (fabs(R->tbut2.x - R->tbut1.x) > fabs(R->tbut2.y - R->tbut1.y))
	{
		R->u0 = (R->tbut1.x - RO1.x) * (ET[1]->w - 1) / (RO2.x - RO1.x);
		R->u1 = (R->tbut2.x - RO1.x) * (ET[1]->w - 1) / (RO2.x - RO1.x);
	}
	else
	{
		R->u0 = (R->tbut1.y - RO1.y) * (ET[1]->w - 1) / (RO2.y - RO1.y);
		R->u1 = (R->tbut2.y - RO1.y) * (ET[1]->w - 1) / (RO2.y - RO1.y);
	}
}

static void	butintersect(t_rend *rend, t_env *env)
{
	if (R->tbut1.y <= 0 || R->tbut2.y <= 0)
	{
		R->nfz.x = 1e-4;
		R->nfz.y = 5;
		R->nfside.x = 1e-5;
		R->nfside.y = 20;
		R->wintsect1.x = -R->nfside.x;
		R->wintsect1.y = R->nfz.x;
		R->wintsect2.x = -R->nfside.y;
		R->wintsect2.y = R->nfz.y;
		R->i1 = intersect(R->tbut1, R->tbut2,
					R->wintsect1, R->wintsect2);
		R->wintsect1.x = R->nfside.x;
		R->wintsect2.x = R->nfside.y;
		R->i2 = intersect(R->tbut1, R->tbut2,
					R->wintsect1, R->wintsect2);
		RO1 = (t_xy){R->tbut1.x, R->tbut1.y};
		RO2 = (t_xy){R->tbut2.x, R->tbut2.y};
		butintersect_support(R, env);
	}
}

t_scaler	scaler_init_support1(t_rend *rend)
{
	t_scaler temp;

	temp = (t_scaler)
	{R->buty1a + (R->butbegx - 1 - R->butx1) *
		(R->buty2a - R->buty1a) / (R->butx2 - R->butx1),
		((R->buty2a < R->buty1a) ^
		(R->butx2 < R->butx1)) ? -1 : 1,
		abs(R->buty2a - R->buty1a),
		abs(R->butx2 - R->butx1),
		(int)((R->butbegx - 1 - R->butx1) * abs(R->buty2a -
		R->buty1a)) % abs(R->butx2 - R->butx1)};
	return (temp);
}

t_scaler	scaler_init_support2(t_rend *rend)
{
	t_scaler temp;

	temp = (t_scaler)
	{R->buty1b + (R->butbegx - 1 - R->butx1) *
		(R->buty2b - R->buty1b) / (R->butx2 - R->butx1),
		((R->buty2b < R->buty1b) ^
		(R->butx2 < R->butx1)) ? -1 : 1,
		abs(R->buty2b - R->buty1b),
		abs(R->butx2 - R->butx1),
		(int)((R->butbegx - 1 - R->butx1) * abs(R->buty2b -
		R->buty1b)) % abs(R->butx2 - R->butx1)};
	return (temp);
}

void		butplane_support3(t_rend *rend, t_env *env)
{
	R->buty1a = HWIN / 2 - (int)(YAW(R->butceil, R->tbut1.y) * R->butyscale1);
	R->buty1b = HWIN / 2 - (int)(YAW(R->butfloor, R->tbut1.y) * R->butyscale1);
	R->buty2a = HWIN / 2 - (int)(YAW(R->butceil, R->tbut2.y) * R->butyscale2);
	R->buty2b = HWIN / 2 - (int)(YAW(R->butfloor, R->tbut2.y) * R->butyscale2);
}

void		butplane_support(t_rend *rend, int j, t_env *env)
{
	R->butx2 = WWIN / 2 - (int)((R->tbut2.x) * R->butxscale2);
	if (R->butx1 == R->butx2 || R->butx1 > R->sprq[j].sx2 ||
				R->butx2 < R->sprq[j].sx1)
		return ;
	R->butceil = R->nowsect->floor + 5 + BUTTONHEIGHT - EPW.z;
	R->butfloor = R->nowsect->floor + 5 - EPW.z;
	butplane_support3(rend, env);
	R->butbegx = MAX(R->butx1, R->sprq[j].sx1);
	R->butendx = MIN(R->butx2, R->sprq[j].sx2);
	R->butx = R->butbegx;
	R->butya_int = scaler_init_support1(R);
	R->butyb_int = scaler_init_support2(R);
	while (R->butx++ < R->butendx)
	{
		R->butya = scaler_next(&R->butya_int);
		R->cbutya = CLAMP(R->butya, R->sprq[j].ytop[R->butx],
					R->sprq[j].ybottom[R->butx]);
		R->butyb = scaler_next(&R->butyb_int);
		R->cbutyb = CLAMP(R->butyb, R->sprq[j].ytop[R->butx],
					R->sprq[j].ybottom[R->butx]);
		R->txtx = (int)((double)(R->butx - R->butx1) /
				(double)(R->butx2 - R->butx1) * ET[1]->w);
		drawbutton(env, R);
	}
}

void		butplane_support2(t_env *env, t_rend *rend)
{
	R->tbut1.x = R->vbut1.x * EPSIN - R->vbut1.y * EPCOS;
	R->tbut1.y = R->vbut1.x * EPCOS + R->vbut1.y * EPSIN;
	R->tbut2.x = R->vbut2.x * EPSIN - R->vbut2.y * EPCOS;
	R->tbut2.y = R->vbut2.x * EPCOS + R->vbut2.y * EPSIN;
}

void		butplane(t_env *env, t_rend *rend, int j)
{
	if (R->sprq[j].visible == 0 || env->button[j].visible == 0)
		return ;
	R->nowsect = &(ESEC[R->sprq[j].sector]);
	R->vbut1.x = env->button[j].x1 - EPW.x;
	R->vbut1.y = env->button[j].y1 - EPW.y;
	R->vbut2.x = env->button[j].x2 - EPW.x;
	R->vbut2.y = env->button[j].y2 - EPW.y;
	butplane_support2(env, rend);
	if (R->tbut1.y <= 0 && R->tbut2.y <= 0)
		return ;
	butintersect(R, env);
	if (R->tbut1.y <= 0.5)
	{
		R->tbut1.x = (0.5 - R->tbut1.y) * (R->tbut2.x - R->tbut1.x) /
				(R->tbut2.y - R->tbut1.y) + R->tbut1.x;
		R->tbut1.y = 0.5;
	}
	R->butxscale1 = WWIN * HFOV / R->tbut1.y;
	R->butyscale1 = HWIN * VFOV / R->tbut1.y;
	R->butx1 = WWIN / 2 - (int)((R->tbut1.x) * R->butxscale1);
	R->butxscale2 = WWIN * HFOV / R->tbut2.y;
	R->butyscale2 = HWIN * VFOV / R->tbut2.y;
	butplane_support(R, j, env);
}

void		renderbutton(t_env *env, t_rend *rend)
{
	int i;

	i = -1;
	while (++i < (int)env->nsectors)
	{
		R->u0 = 0;
		R->u1 = ET[1]->w;
		butplane(env, R, i);
	}
}
