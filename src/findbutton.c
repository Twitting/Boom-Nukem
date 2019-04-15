/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbutton.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daharwoo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:33:24 by ebednar           #+#    #+#             */
/*   Updated: 2019/04/15 12:29:24 by daharwoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	findbutton_di(t_env *env, int i, int s, t_xy *xy)
{
	if (ESIV[s % ESIN].x < ESIV[(s + 1) % ESIN].x)
		xy->x = EBUTT.x1 + 0.1;
	else
		xy->x = EBUTT.x1 - 0.1;
	xy->y = (xy->x - ESIV[s % ESIN].x) *
	(ESIV[(s + 1) % ESIN].y -
	ESIV[s % ESIN].y) / (ESIV[(s + 1) %
	ESIN].x - ESIV[s % ESIN].x) +
	ESIV[s % ESIN].y;
	while (((xy->x - EBUTT.x1) * (xy->x - EBUTT.x1) +
			(xy->y - EBUTT.y1) * (xy->y - EBUTT.y1)) < BUTTONWIDTH)
	{
		xy->y = (xy->x - ESIV[s % ESIN].x) *
		(ESIV[(s + 1) % ESIN].y -
		ESIV[s % ESIN].y) / (ESIV[(s + 1) %
		ESIN].x - ESIV[s % ESIN].x) +
		ESIV[s % ESIN].y;
		if (ESIV[s % ESIN].x < ESIV[(s + 1) % ESIN].x)
			xy->x += 0.1;
		else
			xy->x -= 0.1;
	}
}

void	findbutton_hv(t_env *env, int i, int s)
{
	t_xy	xy;

	EBUTT.x1 = (ESIV[s % ESIN].x + ESIV[(s + 1) % ESIN].x) / 2;
	EBUTT.y1 = (ESIV[s % ESIN].y + ESIV[(s + 1) % ESIN].y) / 2;
	if (ESIV[s % ESIN].x == ESIV[(s + 1) % ESIN].x)
	{
		xy.x = EBUTT.x1;
		if (ESIV[s % ESIN].y < ESIV[(s + 1) % ESIN].y)
			xy.y = EBUTT.y1 + BUTTONWIDTH;
		else
			xy.y = EBUTT.y1 - BUTTONWIDTH;
	}
	else if (ESIV[s % ESIN].y == ESIV[(s + 1) % ESIN].y)
	{
		xy.y = EBUTT.y1;
		if (ESIV[s % ESIN].x < ESIV[(s + 1) % ESIN].x)
			xy.x = EBUTT.x1 + BUTTONWIDTH;
		else
			xy.x = EBUTT.x1 - BUTTONWIDTH;
	}
	else
		findbutton_di(env, i, s, &xy);
	EBUTT.x2 = xy.x;
	EBUTT.y2 = xy.y;
}

void	findbutton(t_env *env)
{
	unsigned int	s;
	unsigned int	i;

	i = -1;
	while (++i < env->nsectors)
	{
		s = -1;
		EBUTT.visible = 0;
		while (++s < ESIN)
		{
			if (ESEC[i].neighbors[s] == -2)
			{
				EBUTT.visible = 1;
				findbutton_hv(env, i, s);
			}
		}
	}
}
