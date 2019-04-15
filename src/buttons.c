/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:47:12 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 15:48:17 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"

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
