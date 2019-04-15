/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlines.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:53:52 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 16:21:33 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_scaler	scaler_init_support7(t_rend *rend, t_env *env)
{
	t_scaler temp;

	temp = (t_scaler)
	{0 + (R->cya - 1 - R->ya) *
		((ET[0]->w - 1)) / (R->yb - R->ya),
		(((ET[0]->w - 1) < 0) ^
		(R->yb < R->ya)) ? -1 : 1,
		abs((ET[0]->w - 1)),
		abs(R->yb - R->ya),
		(int)((R->cya - 1 - R->ya) * abs((ET[0]->w - 1)))
		% abs(R->yb - R->ya)};
	return (temp);
}

t_scaler	scaler_init_support8(t_rend *rend, t_env *env)
{
	t_scaler temp;

	temp = (t_scaler)
	{0 + (R->ncyb + 1 - 1 - R->ya) *
		((ET[0]->w - 1)) / (R->yb - R->ya),
		(((ET[0]->w - 1) < 0) ^
		(R->yb < R->ya)) ? -1 : 1,
		abs((ET[0]->w - 1) - 0),
		abs(R->yb - R->ya),
		(int)((R->ncyb - R->ya) * abs((ET[0]->w - 1) -
		0)) % abs(R->yb - R->ya)};
	return (temp);
}

void		vlinebot(t_env *env, t_rend *rend)
{
	int			*pix;
	int			y;
	int			txty;
	t_scaler	txy;

	txy = (t_scaler)scaler_init_support8(R, env);
	pix = (int*)env->surface->pixels;
	R->ncyb = CLAMP((R->ncyb + 1), 0, HWIN - 1);
	R->ncya = CLAMP(R->cyb, 0, HWIN - 1) + 2;
	pix += (R->ncyb + 1) * WWIN + R->x;
	y = R->ncyb + 1;
	while (++y <= R->cyb)
	{
		txty = scaler_next(&txy) * (R->nowsect->ceiling -
		R->nowsect->floor) / 64;
		*pix = ((int *)(R->NST[1]->pixels))[txty % R->NST[1]->h *
		R->NST[1]->w + R->txtx % R->NST[1]->w];
		pix += WWIN;
	}
}

void		vlinetop(t_env *env, t_rend *rend)
{
	int			*pix;
	int			y;
	int			txty;
	t_scaler	txy;

	txy = (t_scaler)scaler_init_support7(R, env);
	pix = (int*)env->surface->pixels;
	R->cya = CLAMP(R->cya, 0, HWIN - 1) - 1;
	R->ncya = CLAMP(R->ncya - 1, 0, HWIN - 1) + 2;
	pix += R->cya * WWIN + R->x;
	y = R->cya;
	while (++y <= R->ncya - 1)
	{
		txty = scaler_next(&txy) * (R->nowsect->ceiling -
		R->nowsect->floor) / 64;
		*pix = ((int *)(R->NST[1]->pixels))[txty % R->NST[1]->h *
		R->NST[1]->w + R->txtx % R->NST[1]->w];
		pix += WWIN;
	}
}

void		vlinewall(t_env *env, t_rend *rend)
{
	int			*pix;
	int			y;
	int			txty;
	t_scaler	txy;

	txy = (t_scaler)scaler_init_support7(R, env);
	pix = (int*)env->surface->pixels;
	R->cya = CLAMP(R->cya, 0, HWIN - 1) - 1;
	R->cyb = CLAMP(R->cyb, 0, HWIN - 1) + 2;
	pix += R->cya * WWIN + R->x;
	y = R->cya;
	while (++y <= R->cyb)
	{
		txty = scaler_next(&txy) * (R->nowsect->ceiling -
		R->nowsect->floor) / 64;
		*pix = ((int *)(R->NST[1]->pixels))[txty % R->NST[1]->h *
		R->NST[1]->w + R->txtx % R->NST[1]->w];
		pix += WWIN;
	}
}
