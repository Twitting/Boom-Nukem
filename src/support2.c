/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:37 by daharwoo          #+#    #+#             */
/*   Updated: 2019/04/15 15:48:54 by daharwoo         ###   ########.fr       */
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
