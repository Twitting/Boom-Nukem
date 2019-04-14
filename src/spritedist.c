/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritedist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:26:48 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/14 15:31:34 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	spritedist(t_env *env)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++i < env->sprcount)
	{
		if (ESPRI.type == 2)
		{
			x = (ESPRI.pos1.x + ESPRI.pos2.x) / 2;
			y = (ESPRI.pos1.y + ESPRI.pos2.y) / 2;
			ESPRI.spritedist = (EPW.x - x) *
			(EPW.x - x) + (EPW.y - y) *
			(EPW.y - y);
		}
		else
			ESPRI.spritedist = (EPW.x - ESPRI.pos1.x) *
			(EPW.x - ESPRI.pos1.x) + (EPW.y -
			ESPRI.pos1.y) * (EPW.y - ESPRI.pos1.y);
		if (ESPRI.type != 2)
			ESPRI.visible = 0;
	}
}

void	drawtransp(t_env *env, t_rend *R, int j)
{
	int	y;
	int	*pix;
	int	txty;

	pix = (int*)env->surface->pixels;
	pix += R->ctrya * WWIN + R->trx;
	y = R->ctrya - 1;
	while (++y <= R->ctryb)
	{
		txty = (int)((double)(y - R->trya) /
				(double)(R->tryb - R->trya) *
				ESJT0->h);
		if (((int *)(ESJT0->pixels))[txty %
				ESJT0->h *
				ESJT0->w + R->txtx] != 0)
			*pix = ((int *)(ESJT0->pixels))[txty %
				ESJT0->h *
				ESJT0->w + R->txtx];
		pix += WWIN;
	}
}

void	sortsprite(t_env *env)
{
	int			f;
	int			i;
	t_sprite	temp;

	f = 1;
	while (f == 1)
	{
		f = 0;
		i = 0;
		while (i < env->sprcount - 1)
		{
			if (ESPRI.spritedist < env->sprite[i + 1].spritedist)
			{
				temp = ESPRI;
				ESPRI = env->sprite[i + 1];
				env->sprite[i + 1] = temp;
				f = 1;
				break ;
			}
			i++;
		}
	}
}
