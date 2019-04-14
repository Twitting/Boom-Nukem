/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightswitch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebednar <ebednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:15:36 by twitting          #+#    #+#             */
/*   Updated: 2019/04/14 18:44:40 by ebednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	currentsectorlightapply(t_env *env, int secnum)
{
	unsigned char	*pix;
	int				ijkt[4];

	ijkt[3] = -1;
	while (++ijkt[3] < 3)
	{
		ijkt[0] = secnum;
		if (ESEC[ijkt[0]].sky == 1)
			ESEC[ijkt[0]].light = 100;
		if (ESECT != NULL)
			SDL_FreeSurface(ESECT);
		ESECT =
			IMG_Load(gettex(env, ijkt[0], ijkt[3]));
		pix = (unsigned char *)ESECT->pixels;
		ijkt[1] = -1;
		while (++ijkt[1] < ESECT->h)
		{
			ijkt[2] = -1;
			while (++ijkt[2] < ESECT->w)
				sectorlightapply_support(env, ijkt, pix);
		}
	}
}

void	currentspritelight(t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->sprcount)
	{
		j = -1;
		if (ESPRI.sector == (int)EPS)
		{
			if (ESPRI.type == 0 || ESPRI.type == 3)
				spritelightapply(env, &ESPRI);
			if (ESPRI.type == 1 || ESPRI.type == 4)
			{
				if (ESPRI.type == 4)
					enemylightapply(env, &ESPRI, 0);
				else
					while (++j < 7)
						enemylightapply(env, &ESPRI, j);
			}
			else if (ESPRI.type == 5)
				while (++j < 8)
					keylightapply(env, &ESPRI, j);
		}
	}
}

int		checkswitch(t_env *env)
{
	double	buttondist;

	buttondist =
	(EPW.x - (env->button[EPS].x1 +
	env->button[EPS].x2) / 2) *
	(EPW.x - (env->button[EPS].x1 +
	env->button[EPS].x2) / 2) +
	(EPW.y - (env->button[EPS].y1 +
	env->button[EPS].y2) / 2) *
	(EPW.y - (env->button[EPS].y1 +
	env->button[EPS].y2) / 2);
	if (buttondist <= 10)
		return (1);
	return (0);
}

void	pushswitch(t_env *env)
{
	int	i;

	if (env->player.pushingbutton)
	{
		if (ESEC[EPS].on == 0)
		{
			ESEC[EPS].on = 1;
			ESEC[EPS].light += 40;
		}
		else if (ESEC[EPS].on == 1)
		{
			ESEC[EPS].on = 0;
			ESEC[EPS].light -= 40;
		}
		currentsectorlightapply(env, EPS);
		currentspritelight(env);
		env->player.pushingbutton = 0;
		i = -1;
	}
}
