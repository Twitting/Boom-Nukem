/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallintersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:12:44 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/12 12:13:01 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	wallintersect_1(t_rend *rend)
{
	RO1 = (t_xy){rend->t1.x, rend->t1.y};
	RO2 = (t_xy){rend->t2.x, rend->t2.y};
	if (rend->t1.y < rend->nfz.x)
	{
		if (rend->i1.y > 0)
		{
			rend->t1.x = rend->i1.x;
			rend->t1.y = rend->i1.y;
		}
		else
		{
			rend->t1.x = rend->i2.x;
			rend->t1.y = rend->i2.y;
		}
	}
}

void	wallintersect_2(t_rend *rend, t_env *env)
{
	if (rend->t2.y < rend->nfz.x)
	{
		if (rend->i1.y > 0)
		{
			rend->t2.x = rend->i1.x;
			rend->t2.y = rend->i1.y;
		}
		else
		{
			rend->t2.x = rend->i2.x;
			rend->t2.y = rend->i2.y;
		}
	}
	if (fabs(rend->t2.x - rend->t1.x) > fabs(rend->t2.y - rend->t1.y))
	{
		rend->u0 = (rend->t1.x - RO1.x) * (env->text[0]->w - 1) / (RO2.x - RO1.x);
		rend->u1 = (rend->t2.x - RO1.x) * (env->text[0]->w - 1) / (RO2.x - RO1.x);
	}
	else
	{
		rend->u0 = (rend->t1.y - RO1.y) * (env->text[0]->w - 1) / (RO2.y - RO1.y);
		rend->u1 = (rend->t2.y - RO1.y) * (env->text[0]->w - 1) / (RO2.y - RO1.y);
	}
}

void	wallintersect(t_rend *rend, t_env *env)
{
	if (rend->t1.y <= 0 || rend->t2.y <= 0)
	{
		rend->nfz.x = 1e-4;
		rend->nfz.y = 5;
		rend->nfside.x = 1e-5;
		rend->nfside.y = 20;
		rend->wintsect1.x = -rend->nfside.x;
		rend->wintsect1.y = rend->nfz.x;
		rend->wintsect2.x = -rend->nfside.y;
		rend->wintsect2.y = rend->nfz.y;
		rend->i1 = intersect(rend->t1, rend->t2, rend->wintsect1, rend->wintsect2);
		rend->wintsect1.x = rend->nfside.x;
		rend->wintsect2.x = rend->nfside.y;
		rend->i2 = intersect(rend->t1, rend->t2, rend->wintsect1, rend->wintsect2);
		wallintersect_1(rend);
		wallintersect_2(rend, env);
	}
}
